#define VERSION	"tig-0.6.git"
	"git ls-remote $(git rev-parse --git-dir) 2>/dev/null"
	unsigned int remote:1;	/* Is it a remote ref? */
#define string_copy_rev(dst, src) \
	string_ncopy_do(dst, SIZEOF_REV, src, SIZEOF_REV - 1)

	if (bufsize < SIZEOF_STR)
		buf[bufsize] = 0;

static bool opt_rev_graph		= FALSE;
			string_copy(opt_cmd, "git log --pretty=raw");
LINE(MAIN_REMOTE,  "",			COLOR_YELLOW,	COLOR_DEFAULT,	A_BOLD), \
	char *sep = "";
	/* Open and reads in all view content. */
	bool (*open)(struct view *view);
	/* Draw one line; @lineno must be < view->height. */
	bool (*draw)(struct view *view, struct line *line, unsigned int lineno, bool selected);
static struct view_ops help_ops;
	VIEW_(HELP,  "help",  &help_ops,  ""),
	VIEW_(PAGER, "pager", &pager_ops, ""),
		view->offset += scroll_steps;
		assert(0 <= view->offset && view->offset < view->lines);
		/* When running random commands, initially show the
		 * command in the title. However, it maybe later be
		 * overwritten if a commit line is selected. */
		string_copy(view->ref, view->cmd);
		char path[SIZEOF_STR];
			opt_path[0] = path[0] = 0;
		else if (sq_quote(path, 0, opt_path) >= sizeof(path))
			return FALSE;
		if (!string_format(view->cmd, format, id, path))

		/* Put the current ref_* value to the view title ref
		 * member. This is needed by the blob view. Most other
		 * views sets it automatically after loading because the
		 * first line is a commit line. */
		string_copy(view->ref, id);
	string_copy_rev(view->vid, id);
			ret = iconv(opt_iconv, &inbuf, &inlen, &outbuf, &outlen);
		/* Since revision graph visualization requires knowledge
		 * about the parent commit, it causes a further one-off
		 * needed to be redrawn for incremental updates. */
		if (redraw_from > 0 && opt_rev_graph)
			redraw_from--;

static struct line *
add_line_text(struct view *view, char *data, enum line_type type)
	struct line *line = &view->line[view->lines];
	if (!data)
		return NULL;
	line->data = strdup(data);
	if (!line->data)
		return NULL;
	line->type = type;
	view->lines++;
	return line;
}
/*
 * View opening
 */
	if (view->ops->open) {
		if (!view->ops->open(view)) {
			report("Failed to load %s view", view->name);
			return;
		}
			report("No file chosen, press %s to open tree view",
			       get_key(REQ_VIEW_TREE));
		open_view(view, request, OPEN_DEFAULT);
		break;

	case REQ_VIEW_PAGER:
		if (!VIEW(REQ_VIEW_PAGER)->lines) {
			report("No pager content, press %s to run command from prompt",
			       get_key(REQ_PROMPT));
			break;
		}
		open_view(view, request, OPEN_DEFAULT);
		break;

	if (!string_format(refbuf, "git describe %s 2>/dev/null", commit_id))
		char *fmt = ref->tag    ? "%s[%s]" :
		            ref->remote ? "%s<%s>" : "%s%s";
	add_line_text(view, buf, LINE_PP_REFS);
	struct line *line;
	line = add_line_text(view, data, get_line_type(data));
	if (!line)
		char *text = line->data + STRING_SIZE("commit ");
		if (view != VIEW(REQ_VIEW_PAGER))
			string_copy_rev(view->ref, text);
		string_copy_rev(ref_commit, text);
	NULL,
	pager_draw,
	pager_enter,
	pager_grep,
	pager_select,
};


/*
 * Help backend
 */

static bool
help_open(struct view *view)
{
	char buf[BUFSIZ];
	int lines = ARRAY_SIZE(req_info) + 2;
	int i;

	if (view->lines > 0)
		return TRUE;

	for (i = 0; i < ARRAY_SIZE(req_info); i++)
		if (!req_info[i].request)
			lines++;

	view->line = calloc(lines, sizeof(*view->line));
	if (!view->line)
		return FALSE;

	add_line_text(view, "Quick reference for tig keybindings:", LINE_DEFAULT);

	for (i = 0; i < ARRAY_SIZE(req_info); i++) {
		char *key;

		if (!req_info[i].request) {
			add_line_text(view, "", LINE_DEFAULT);
			add_line_text(view, req_info[i].help, LINE_DEFAULT);
			continue;
		}

		key = get_key(req_info[i].request);
		if (!string_format(buf, "    %-25s %s", key, req_info[i].help))
			continue;

		add_line_text(view, buf, LINE_DEFAULT);
	}

	return TRUE;
}

static struct view_ops help_ops = {
	"line",
	help_open,
	NULL,
	pager_draw,
		if (!string_format(buf, "Directory path /%s", opt_path) ||
		    !realloc_lines(view, view->line_size + 1) ||
		    !add_line_text(view, buf, LINE_DEFAULT))
		if (*opt_path) {
			if (!string_format(buf, TREE_UP_FORMAT, view->ref) ||
			    !realloc_lines(view, view->line_size + 1) ||
			    !add_line_text(view, buf, LINE_TREE_DIR))
				return FALSE;
		}
	if (!add_line_text(view, text, type))
	char *text = line->data + STRING_SIZE("100644 blob ");
		string_copy_rev(ref_blob, text);
	string_copy_rev(view->ref, text);
	NULL,
	pager_draw,
	return add_line_text(view, line, LINE_DEFAULT);
	NULL,
	pager_draw,
			else if (commit->refs[i]->remote)
				wattrset(view->win, get_line_attr(LINE_MAIN_REMOTE));
		string_copy_rev(commit->id, line);
		/* Parse author lines where the name may be empty:
		 *	author  <email@address.tld> 1138474660 +0100
		 */
		char *nameend = strchr(ident, '<');
		char *emailend = strchr(ident, '>');
		if (!commit || !nameend || !emailend)
		*nameend = *emailend = 0;
		ident = chomp_string(ident);
		if (!*ident) {
			ident = chomp_string(nameend + 1);
			if (!*ident)
				ident = "Unknown";
		if (emailend[1] == ' ') {
			char *secs = emailend + 2;
			char *zone = strchr(secs, ' ');
			time_t time = (time_t) atol(secs);

	string_copy_rev(view->ref, commit->id);
	string_copy_rev(ref_commit, view->ref);
	NULL,
	main_draw,
	bool remote = FALSE;
	} else if (!strncmp(name, "refs/remotes/", STRING_SIZE("refs/remotes/"))) {
		remote = TRUE;
		namelen -= STRING_SIZE("refs/remotes/");
		name	+= STRING_SIZE("refs/remotes/");

	ref->remote = remote;
	string_copy_rev(ref->id, id);