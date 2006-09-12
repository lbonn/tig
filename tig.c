#define SIZEOF_REV	41	/* Holds a SHA-1 and an ending NUL */

/* Revision graph */

#define REVGRAPH_INIT	'I'
#define REVGRAPH_MERGE	'M'
#define REVGRAPH_BRANCH	'+'
#define REVGRAPH_COMMIT	'*'
#define REVGRAPH_LINE	'|'

/* Size of rev graph with no  "padding" columns */
#define SIZEOF_REVITEMS	(SIZEOF_REVGRAPH - (SIZEOF_REVGRAPH / 2))

	char id[SIZEOF_REV];	/* Commit SHA1 ID */
LINE(ACKED,	   "    Acked-by",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \
/* Parse output from git-ls-tree(1):
			char *data = line->data;
	char *text = line->data;

	text += STRING_SIZE("100644 blob ");
	if (line->type == LINE_TREE_FILE) {
		string_ncopy(ref_blob, text, 40);
		/* Also update the blob view's ref, since all there must always
		 * be in sync. */
		string_copy(VIEW(REQ_VIEW_BLOB)->ref, ref_blob);

	} else if (line->type != LINE_TREE_DIR) {
		return;

	string_ncopy(view->ref, text, 40);
	char id[SIZEOF_REV];		/* SHA1 ID. */

struct rev_stack {
	char rev[SIZEOF_REVITEMS][SIZEOF_REV];
	size_t size;
};

/* The current stack of revisions on the graph. */
static struct rev_stack graph_stacks[3];
static size_t graph_stack_no;

/* Parents of the commit being visualized. */
static struct rev_stack graph_parents[2];

static size_t graph_last_rev;

static void
push_rev_stack(struct rev_stack *stack, char *parent)
{
	fprintf(stderr, " (%s)", parent);

	/* Combine duplicate parents lines. */
	if (stack->size > 0 &&
	    !strncmp(stack->rev[stack->size - 1], parent, SIZEOF_REV))
		return;

	if (stack->size < SIZEOF_REVITEMS) {
		string_ncopy(stack->rev[stack->size++], parent, SIZEOF_REV);
	}
}

static void
draw_rev_graph(struct commit *commit, size_t stackpos,
	       struct rev_stack *stack, struct rev_stack *parents,
	       struct rev_stack *prev_parents)
{
	chtype symbol, separator, line;
	size_t i;

	/* Place the symbol for this commit. */
	if (parents->size == 0)
		symbol = REVGRAPH_INIT;
	else if (parents->size > 1)
		symbol = REVGRAPH_MERGE;
	else if (stackpos >= stack->size)
		symbol = REVGRAPH_BRANCH;
	else
		symbol = REVGRAPH_COMMIT;

	separator = ' ';
	line = REVGRAPH_LINE;

	for (i = 0; i < stackpos; i++) {
		commit->graph[commit->graph_size++] = line;
		if (prev_parents->size > 1 &&
		    i == graph_last_rev) {
			separator = '`';
			line = '.';
		}
		commit->graph[commit->graph_size++] = separator;
	}

	commit->graph[commit->graph_size++] = symbol;

	separator = ' ';
	line = REVGRAPH_LINE;
	i++;

	for (; i < stack->size; i++) {
		commit->graph[commit->graph_size++] = separator;
		commit->graph[commit->graph_size++] = line;
		if (prev_parents->size > 1) {
			if (i < graph_last_rev + prev_parents->size) {
				separator = '`';
				line = '.';
			}
		}
	}
}

void
update_rev_graph(struct commit *commit)
{
	struct rev_stack *parents = &graph_parents[graph_stack_no & 1];
	struct rev_stack *stack = &graph_stacks[graph_stack_no++ & 1];
	struct rev_stack *prev_parents = &graph_parents[graph_stack_no & 1];
	struct rev_stack *graph = &graph_stacks[graph_stack_no & 1];
	size_t stackpos = 0;
	size_t i;

	fprintf(stderr, "\n%p <%s> ", graph, commit->id);

	/* First traverse all lines of revisions up to the active one. */
	for (stackpos = 0; stackpos < stack->size; stackpos++) {
		if (!strcmp(stack->rev[stackpos], commit->id))
			break;

		push_rev_stack(graph, stack->rev[stackpos]);
	}

	assert(commit->graph_size < ARRAY_SIZE(commit->graph));

	for (i = 0; i < parents->size; i++)
		push_rev_stack(graph, parents->rev[i]);

	/* FIXME: Moving branches left and right when collapsing a branch. */
	for (i = stackpos + 1; i < stack->size; i++)
		push_rev_stack(graph, stack->rev[i]);

	draw_rev_graph(commit, stackpos, stack, parents, prev_parents);
	graph_last_rev = stackpos;
	stack->size = prev_parents->size = 0;
}

		fprintf(stderr, "\n%p [%s]", &graph_stacks[graph_stack_no & 1], commit->id);
		break;

	case LINE_PARENT:
		if (commit) {
			line += STRING_SIZE("parent ");
			push_rev_stack(&graph_parents[graph_stack_no & 1], line);
		}
		update_rev_graph(commit);
