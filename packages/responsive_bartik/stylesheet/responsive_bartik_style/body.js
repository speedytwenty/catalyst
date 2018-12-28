/* ------------------- Overall Specifications ------------- */

body {
  line-height: 1.5;
  font-size: 87.5%;
  word-wrap: break-word;
  margin: 0;
  padding: 0;
  border: 0;
  outline: 0;
}
a:link,
a:visited {
  text-decoration: none;
}
a:hover,
a:active,
a:focus {
  text-decoration: underline;
}
h1,
h2,
h3,
h4,
h5,
h6 {
  margin: 1.0em 0 0.5em;
  font-weight: inherit;
}
h1 {
  font-size: 1.357em;
  color: #000;
}
h2 {
  font-size: 1.143em;
}
p {
  margin: 0 0 1.2em;
}
del {
  text-decoration: line-through;
}
tr.odd {
  background-color: #dddddd;
}
img {
  outline: 0;
}

/**
 * The generic monospace font family is listed before Courier new to avoid a
 * a bug in font-size rendering:
 * http://meyerweb.com/eric/thoughts/2010/02/12/fixed-monospace-sizing
 */
code,
pre,
kbd,
samp,
var {
  padding: 0 0.4em;
  font-size: 0.77em;
  font-family: Menlo, Consolas, "Andale Mono", "Lucida Console", "Nimbus Mono L", "DejaVu Sans Mono", monospace, "Courier New";
}
code {
  background-color: #f2f2f2;
  background-color: rgba(40, 40, 0, 0.06);
}
pre code,
pre kbd,
pre samp,
pre var,
kbd kbd,
kbd samp,
code var {
  font-size: 100%;
  background-color: transparent;
}
pre code,
pre samp,
pre var {
  padding: 0;
}
.description code {
  font-size: 1em;
}
kbd {
  background-color: #f2f2f2;
  border: 1px outset #575757;
  margin: 0 3px;
  color: #666;
  display: inline-block;
  padding: 0 6px;
  border-radius: 5px;
}
pre {
  background-color: #f2f2f2;
  background-color: rgba(40, 40, 0, 0.06);
  margin: 10px 0;
  overflow: hidden;
  padding: 15px;
  white-space: pre-wrap;
}


/* ------------------- Fonts ------------------------------ */

body,
#site-slogan,
.ui-widget,
.comment-form label {
  font-family: Georgia, "Times New Roman", Times, serif;
}
#header,
#footer-wrapper,
#skip-link,
ul.contextual-links,
ul.links,
ul.primary,
.item-list .pager,
div.field-type-taxonomy-term-reference,
div.messages,
div.meta,
p.comment-time,
table,
.breadcrumb {
  font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
}
input,
textarea,
select,
a.button {
  font-family: "Lucida Grande", "Lucida Sans Unicode", Verdana, sans-serif;
}

/* ------------------- Reset Styles ----------------------- */

caption {
  text-align: left; /* LTR */
  font-weight: normal;
}
blockquote {
  background: #f7f7f7;
  border-left: 1px solid #bbb;
  font-style: italic;
  margin: 1.5em 10px;
  padding: 0.5em 10px;
}
blockquote:before {
  color: #bbb;
  content: "\201C";
  font-size: 3em;
  line-height: 0.1em;
  margin-right: 0.2em;
  vertical-align: -.4em;
}
blockquote:after {
  color: #bbb;
  content: "\201D";
  font-size: 3em;
  line-height: 0.1em;
  vertical-align: -.45em;
}
blockquote > p:first-child {
  display: inline;
}
a.feed-icon {
  display: inline-block;
  padding: 15px 0 0 0;
}
img {
  max-width: 100%;
  height: auto;
  border: 0;
}

/* ------------------- Table Styles ----------------------- */

table {
  border: 0;
  border-spacing: 0;
  font-size: 0.857em;
  margin: 10px 0;
  width: 100%;
}
table table {
  font-size: 1em;
}
#footer-wrapper table {
  font-size: 1em;
}
table tr th {
  background: #757575;
  background: rgba(0, 0, 0, 0.51);
  border-bottom-style: none;
}
table tr th,
table tr th a,
table tr th a:hover {
  color: #fff;
  font-weight: bold;
}
table tbody tr th {
  vertical-align: top;
}
tr td,
tr th {
  padding: 4px 9px;
  border: 1px solid #fff;
  text-align: left; /* LTR */
}
#footer-wrapper tr td,
#footer-wrapper tr th {
  border-color: #555;
  border-color: rgba(255, 255, 255, 0.18);
}
tr.odd {
  background: #e4e4e4;
  background: rgba(0, 0, 0, 0.105);
}
tr,
tr.even {
  background: #efefef;
  background: rgba(0, 0, 0, 0.063);
}
table ul.links {
  margin: 0;
  padding: 0;
  font-size: 1em;
}
table ul.links li {
  padding: 0 1em 0 0;
}

/* ------------------- List Styles ------------------------ */

.block ol,
.block ul {
  margin: 0;
  padding: 0 0 0.25em 1em; /* LTR */
}
.contextual-region .contextual .contextual-links a {
  font-size: 0.923em;
  text-shadow: 0 0 0 !important;
}
.item-list .pager {
  font-size: 0.929em;
}
.item-list .pager li {
  padding: 0;
}
.item-list .pager a {
  display: inline-block;
  padding: 10px 15px;
}
.item-list .pager .pager-first a {
  padding: 10px 10px 10px 0;
}
.item-list .pager .pager-previous a {
  padding: 10px 0;
}
.item-list .pager .pager-current {
  padding: 0 10px;
}
.item-list .pager .pager-next a,
.item-list .pager .pager-last a {
  padding: 10px 0 10px 10px;
}
ul.menu li {
  margin: 12px 0;
}

ul.menu li a {
  padding: 10px 0;
}

.region-content ul,
.region-content ol {
  margin: 1em 0;
  padding: 0 0 0.25em 15px; /* LTR */
}
.item-list ul li {
  margin: 0;
  padding: 0.2em 0.5em 0 0; /* LTR */
}
ul.tips {
  padding: 0 0 0 1.25em; /* LTR */
}

/* ------------------- Header ----------------------------- */
#skip-link {
  left: 50%;
  margin-left: -5.25em;
  margin-top: 0;
  position: absolute;
  width: auto;
  z-index: 50;
}
#skip-link a,
#skip-link a:link,
#skip-link a:visited {
  background: #444;
  background: rgba(0, 0, 0, 0.6);
  color: #fff;
  display: block;
  font-size: 0.94em;
  line-height: 1.7;
  padding: 1px 10px 2px 10px;
  text-decoration: none;
  border-radius: 0 0 10px 10px;
}
#skip-link a:hover,
#skip-link a:active,
#skip-link a:focus {
  outline: 0;
}
#logo {
  float: left; /* LTR */
  padding-left: 5px; /* LTR */
}

#name-and-slogan {
  float: left; /* LTR */
  margin: 0;
  padding: 5px 10px 8px;
}
#site-name {
  font-size: 1.6em;
  color: #686868;
  line-height: 1;
}
h1#site-name {
  margin: 0;
}
#site-name a {
  font-weight: normal;
}
#site-slogan {
  font-size: 0.929em;
  margin-top: 7px;
  word-spacing: 0.1em;
  font-style: italic;
}
/* Region header blocks. */
.region-header .block {
  font-size: 0.857em;
  float: left; /* LTR */
  margin: 0 10px;
  padding: 0;
}
.region-header .block .content {
  margin: 0;
  padding: 0;
}
.region-header .block ul {
  margin: 0;
  padding: 0;
}
.region-header .block li {
  list-style: none;
  list-style-image: none;
  padding: 0;
}
.region-header .form-text {
  background: #fefefe;
  background: rgba(255, 255, 255, 0.7);
  border-color: #ccc;
  border-color: rgba(255, 255, 255, 0.3);
  margin-right: 2px; /* LTR */
  width: 120px;
}
.region-header .form-text:hover,
.region-header .form-text:focus,
.region-header .form-text:active {
  background: #fff;
  background: rgba(255, 255, 255, 0.8);
}
.region-header .form-required {
  color: #eee;
  color: rgba(255, 255, 255, 0.7);
}
/* Region header block menus. */
.region-header .block-menu {
  border: 1px solid;
  border-color: #eee;
  border-color: rgba(255, 255, 255, 0.2);
  padding: 0;
  width: 208px;
}
.region-header .block-menu li a {
  display: block;
  border-bottom: 1px solid;
  border-bottom-color: #eee;
  border-bottom-color: rgba(255, 255, 255, 0.2);
  padding: 3px 7px;
}
.region-header .block-menu li a:hover,
.region-header .block-menu li a:focus,
.region-header .block-menu li a:active {
  text-decoration: none;
  background: rgba(255, 255, 255, 0.15);
}
.region-header .block-menu li.last a {
  border-bottom: 0;
}
/* User Login block in the header region */
.region-header #block-user-login {
  width: auto;
}
.region-header #block-user-login .content {
  margin-top: 2px;
}
.region-header #block-user-login .form-item {
  float: left; /* LTR */
  margin: 0;
  padding: 0;
}
.region-header #block-user-login div.item-list,
.region-header #block-user-login div.description {
  font-size: 0.916em;
  margin: 0;
}
.region-header #block-user-login div.item-list {
  clear: both;
}
.region-header #block-user-login div.description {
  display: inline;
}
.region-header #block-user-login .item-list ul {
  padding: 0;
  line-height: 1;
}
.region-header #block-user-login .item-list li {
  list-style: none;
  float: left; /* LTR */
  padding: 3px 0 1px;
}
.region-header #block-user-login .item-list li.last {
  padding-left: 0.5em; /* LTR */
}
.region-header #block-user-login ul.openid-links li.last {
  padding-left: 0; /* LTR */
}
.region-header #user-login-form li.openid-link a,
.region-header #user-login li.openid-link a {
  padding-left: 20px; /* LTR */
}
.region-header #block-user-login .form-actions {
  margin: 4px 0 0;
  padding: 0;
  clear: both;
}
.region-header #block-user-login input.form-submit {
  border: 1px solid;
  border-color: #ccc;
  border-color: rgba(255, 255, 255, 0.5);
  background: #eee;
  background: rgba(255, 255, 255, 0.7);
  margin: 4px 0;
  padding: 3px 8px;
}
.region-header #block-user-login input.form-submit:hover,
.region-header #block-user-login input.form-submit:focus {
  background: #fff;
  background: rgba(255, 255, 255, 0.9);
}
/* Search block in region header. */
.region-header #block-search-form {
  width: 208px;
}
.region-header #block-search-form .form-text {
  width: 154px;
}
/* Language switcher block in region header. */
.region-header .block-locale ul li {
  display: inline;
  padding: 0 0.5em;
}

/* ------------------- Main Menu -------------------------- */
#main-menu {
  clear: both;
}
#main-menu-links {
  font-size: 0.929em;
  margin: 0 5px;
  padding: 0;
  text-align: left; /* LTR */
}
#main-menu-links li {
  float: none;
  list-style: none;
  margin: 0;
  padding: 0;
  width: 100%;
}
#main-menu-links a {
  color: #333;
  background: #ccc;
  background: rgba(255, 255, 255, 0.7);
  float: none;
  display: block;
  text-decoration: none;
  text-shadow: 0 1px #eee;
  border-radius: 8px;
  margin-bottom: 4px;
  padding: 0.9em 0 0.9em 10px;
}
#main-menu-links a:hover,
#main-menu-links a:focus {
  background: #f6f6f2;
  background: rgba(255, 255, 255, 0.95);
}
#main-menu-links a:active {
  background: #b3b3b3;
  background: rgba(255, 255, 255, 1);
}
#main-menu-links li a.active {
  border-bottom: none;
}

/* ------------------- Secondary Menu --------------------- */

#secondary-menu-links {
  float: right; /* LTR */
  font-size: 0.929em;
  margin: 0 10px;
}
#secondary-menu-links  li{
  margin: 0;
  padding: 0;
}
#secondary-menu-links  a {
  display: inline-block;
  padding:  0.8em;
}
#secondary-menu-links a:hover,
#secondary-menu-links a:focus {
  text-decoration: underline;
}

/* ------------------- Main ------------------------------- */

#main {
  margin-top: 20px;
  margin-bottom: 40px;
}

/* ------------------- Featured --------------------------- */

#featured {
  text-align: center;
  font-size: 1.2em;
  font-weight: normal;
  line-height: 1.4;
  padding: 20px 10px 45px;
  margin: 0;
  background: #f0f0f0;
  background: rgba(30, 50, 10, 0.08);
  border-bottom: 1px solid #e7e7e7;
  text-shadow: 1px 1px #fff;
}
#featured h2 {
  font-size: 1.2em;
  line-height: 1;
}
#featured p {
  margin: 0;
  padding: 0;
}

/* ------------------- Highlighted ------------------------ */

#highlighted {
  border-bottom: 1px solid #d3d7d9;
  font-size: 120%;
}

/* ------------------- Help ------------------------------- */

.region-help {
  border: 1px solid #d3d7d9;
  padding: 0 1.5em;
  margin-bottom: 30px;
}

/* ------------------- Content ---------------------------- */

.content {
  margin-top: 0;
}
h1#page-title {
  font-size: 2em;
  line-height: 1;
}
#content h2 {
  margin-bottom: 5px;
  font-size: 1.429em;
  line-height: 1.4;
}
#content h2 a:link {
  padding-top: 18px;

}
.node .content {
  font-size: 1.071em;
}
.node-teaser .content {
  font-size: 1em;
}
.node-teaser h2 {
  margin-top: 0;
  padding-top: 0.5em;
}
.node-teaser h2 a {
  color: #181818;
}
.node-teaser {
  border-bottom: 1px solid #d3d7d9;
  margin-bottom: 30px;
  padding-bottom: 15px;
}
.node-sticky {
  background: #f9f9f9;
  background: rgba(0, 0, 0, 0.024);
  border: 1px solid #d3d7d9;
  padding: 0 15px 15px;
}
.node-full {
  background: none;
  border: none;
  padding: 0;
}
.node-teaser .content {
  clear: none;
  line-height: 1.6;
}

.meta {
  font-size: 0.857em;
  color: #68696b;
  margin-bottom: 10px;
}
.submitted a {
  padding: 10px 0 15px;
}
.submitted .user-picture img {
  float: left; /* LTR */
  height: 20px;
  margin: 1px 5px 0 0; /* LTR */
}

.field-type-taxonomy-term-reference {
  margin: 0 0 1.2em;
}
.field-type-taxonomy-term-reference .field-label {
  font-weight: normal;
  margin: 0;
  padding-right: 5px; /* LTR */
}
.field-type-taxonomy-term-reference .field-label,
.field-type-taxonomy-term-reference ul.links {
  font-size: 0.8em;
}
.view-mode-teaser .field-type-taxonomy-term-reference .field-label,
.view-mode-teaser .field-type-taxonomy-term-reference ul.links {
  font-size: 0.821em;
}
.field-type-taxonomy-term-reference ul.links {
  padding: 0;
  margin: 0;
  list-style: none;
}
.field-type-taxonomy-term-reference ul.links li {
  float: left; /* LTR */
  padding: 0 1em 0 0; /* LTR */
  white-space: nowrap;
}
.field-type-taxonomy-term-reference ul.links li a {
  padding: 5px 0 20px;
}
.link-wrapper {
  text-align: right;
}
.field-type-image img,
.user-picture img {
  margin: 0 0 1em;
}

ul.links {
  color: #68696b;
  font-size: 0.821em;
}
ul.links.inline li a {
  display: inline;
  padding: 18px 0 5px;
}

.unpublished {
  margin: -20px -15px 0;
  padding: 20px 15px 0;
}
.unpublished .comment-text .comment-arrow {
  border-left: 1px solid #fff4f4;
  border-right: 1px solid #fff4f4;
}

/* ------------------- Comments --------------------------- */

.comment h2.title {
  margin-bottom: 1em;
}
.comment div.user-picture img {
  margin-left: 0; /* LTR */
}
.comment {
  margin-bottom: 20px;
  display: table;
  vertical-align: top;
}
.comment .attribution {
  display: table-cell;
  padding: 0 30px 0 0; /* LTR */
  vertical-align: top;
  overflow: hidden;
}
.comment .attribution img {
  margin: 0;
  border: 1px solid #d3d7d9;
}
.comment .attribution .username {
  white-space: nowrap;
}
.comment .submitted p {
  margin: 4px 0;
  font-size: 1.071em;
  line-height: 1.2;
}
.comment .submitted .comment-time {
  font-size: 0.786em;
  color: #68696b;
}
.comment .submitted .comment-permalink {
  font-size: 0.786em;
  text-transform: lowercase;
}
.comment .submitted .comment-permalink a {
  padding: 8px 0 18px;
}
.comment .content {
  font-size: 0.929em;
  line-height: 1.6;
}
.comment .comment-arrow {
  background: url({{ customfilepath('comment-arrow.gif') }}) no-repeat 0 center transparent; /* LTR */
  border-left: 1px solid;
  border-right: 1px solid;
  height: 40px;
  margin-left: -47px; /* LTR */
  margin-top: 10px;
  position: absolute;
  width: 20px;
}
.comment .comment-text {
  padding: 10px 25px;
  border: 1px solid #d3d7d9;
  display: table-cell;
  vertical-align: top;
  position: relative;
  width: 100%;
}
.comment .comment-text h3  a{
  padding-top: 22px;
}
.comment .indented {
  margin-left: 40px; /* LTR */
}
.comment ul.links {
  padding: 0 0 0.25em 0;
}
.comment ul.links li {
  padding: 0 0.5em 0 0; /* LTR */
}
.comment.unpublished {
  margin-right: 5px; /* LTR */
  padding: 5px 2px 5px 5px; /* LTR */
}
.comment.unpublished .comment-text .comment-arrow {
  border-left: 1px solid #fff4f4;
  border-right: 1px solid #fff4f4;
}

/* ------------------- Sidebar ---------------------------- */
.sidebar .section {
  padding-top: 10px;
}
.sidebar .block {
  border: 1px solid;
  padding: 15px 20px;
  margin: 0 0 20px;
}
.sidebar h2 {
  margin: 0 0 0.5em;
  border-bottom: 1px solid #d6d6d6;
  padding-bottom: 5px;
  text-shadow: 0 1px 0 #fff;
  font-size: 1.071em;
  line-height: 1.2;
}
.sidebar .block .content {
  font-size: 0.914em;
  line-height: 1.4;
}
.sidebar tbody {
  border: none;
}
.sidebar tr.even,
.sidebar tr.odd {
  background: none;
  border-bottom: 1px solid #d6d6d6;
}

/* ------------------- Triptych --------------------------- */

#triptych-wrapper {
  background-color: #f0f0f0;
  background: rgba(30, 50, 10, 0.08);
  border-top: 1px solid #e7e7e7;
}
#triptych h2 {
  color: #000;
  font-size: 1.4em;
  margin-bottom: 0.6em;
  text-shadow: 0 1px 0 #fff;
  text-align: center;
  line-height: 1;
}
#triptych .block {
  margin-bottom: 1em;
  padding-bottom: 1em;
  border-bottom: 1px solid #dfdfdf;
  line-height: 1.3;
}
#triptych .block.last {
  border-bottom: none;
}
#triptych .block ul li,
#triptych .block ol li {
  list-style: none;
}
#triptych .block ul,
#triptych .block ol {
  padding-left: 0;
}
#triptych #block-user-login .form-text {
  width: 185px;
}
#triptych #block-user-online p {
  margin-bottom: 0;
}
#triptych #block-node-syndicate h2 {
  overflow: hidden;
  width: 0;
  height: 0;
}
#triptych-last #block-node-syndicate {
  text-align: right;
}
#triptych #block-search-form .form-type-search input {
  width: 185px;
}
#triptych-middle #block-system-powered-by {
  text-align: center;
}
#triptych-last #block-system-powered-by {
  text-align: right;
}

/* ------------------- Footer ----------------------------- */

#footer-wrapper {
  color: #c0c0c0;
  color: rgba(255, 255, 255, 0.65);
  font-size: 0.857em;
}
#footer-wrapper a {
  color: #fcfcfc;
  color: rgba(255, 255, 255, 0.8);
}
#footer-wrapper a:hover,
#footer-wrapper a:focus {
  color: #fefefe;
  color: rgba(255, 255, 255, 0.95);
  text-decoration: underline;
}
#footer-wrapper .block {
  margin: 20px 0;
  border: 1px solid #444;
  border-color: rgba(255, 255, 255, 0.1);
  padding: 10px;
}
#footer-columns .block-menu,
#footer .block {
  margin: 0;
  padding: 0;
  border: none;
}
#footer .block {
  margin: 0.5em 0;
}
#footer .block .content {
  padding: 0.5em 0;
  margin-top: 0;
}
#footer .block h2 {
  margin: 0;
}
#footer-columns h2 {
  border-bottom: 1px solid #555;
  border-color: rgba(255, 255, 255, 0.15);
  font-size: 1em;
  margin-bottom: 0;
  padding-bottom: 3px;
  text-transform: uppercase;
}
#footer-columns .content {
  margin-top: 0;
}
#footer-columns p {
  margin-top: 1em;
}
#footer-columns .content ul {
  list-style: none;
  padding-left: 0; /* LTR */
  margin-left: 0;
}
#footer-columns .content li {
  list-style: none;
  margin: 0;
  padding: 0;
}
#footer-columns .content li a {
  display: block;
  border-bottom: 1px solid #555;
  border-color: rgba(255, 255, 255, 0.15);
  line-height: 1.2;
  padding: 0.8em 2px 0.8em 20px; /* LTR */
  text-indent: -15px;
}
#footer-columns .content li a:hover,
#footer-columns .content li a:focus {
  background-color: #1f1f21;
  background-color: rgba(255, 255, 255, 0.05);
  text-decoration: none;
}
#footer {
  letter-spacing: 0.2px;
  margin-top: 30px;
  border-top: 1px solid #555;
  border-color: rgba(255, 255, 255, 0.15);
}
#footer .region {
  margin-top: 20px;
}
#footer .block {
  clear: both;
}
#footer ul,
#footer li {
  list-style: none;
  margin: 0;
  padding: 0;
}
#footer li a {
  float: left; /* LTR */
  padding: 0 12px;
  display: block;
  border-right: 1px solid #555; /* LTR */
  border-color: rgba(255, 255, 255, 0.15);
}
#footer li.first a {
  padding-left: 0; /* LTR */
}
#footer li.last a {
  padding-right: 0; /* LTR */
  border-right: none; /* LTR */
}
#footer-wrapper tr.odd {
  background-color: transparent;
}
#footer-wrapper tr.even {
  background-color: #2c2c2c;
  background-color: rgba(0, 0, 0, 0.15);
}

/* ------------------- System Tabs ------------------------ */

.tabs {
  font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
  margin-bottom: 20px;
}
.tabs ul.primary {
  padding: 0 3px;
  margin: 0;
  overflow: hidden;
  border: none;
  background: transparent url({{ customfilepath('tabs-border.png') }}) repeat-x left bottom;
}
.tabs ul.primary li {
  display: block;
  float: left; /* LTR */
  vertical-align: bottom;
  margin: 0 5px 0 0; /* LTR */
}
.tabs ul.primary li.active a {
  border-bottom: 1px solid #ffffff;
}
.tabs ul.primary li a {
  color: #000;
  background-color: #ededed;
  height: 1.8em;
  line-height: 1.9;
  display: block;
  font-size: 0.929em;
  float: left; /* not LTR */
  padding: 0 10px 3px;
  margin: 0;
  text-shadow: 0 1px 0 #fff;
  border-top-left-radius: 6px;
  border-top-right-radius: 6px;
}
.tabs ul.primary li.active a {
  background-color: #ffffff;
}
.tabs ul.secondary {
  border-bottom: none;
  padding: 0.5em 0;
}
.tabs ul.secondary li {
  display: block;
  float: left; /* LTR */
}
.tabs ul.secondary li:last-child {
  border-right: none; /* LTR */
}
.tabs ul.secondary li:first-child {
  padding-left: 0; /* LTR */
}
.tabs ul.secondary li a {
  padding: 0.25em 0.5em;
}
.tabs ul.secondary li a.active {
  background: #f2f2f2;
  border-bottom: none;
  border-radius: 5px;
}
ul.action-links {
  list-style: none;
  margin: 5px;
  padding: 0.5em 1em;
}
ul.action-links li {
  display: inline-block;
  margin-left: 10px;
}
ul.action-links li a {
  padding-left: 15px;
  background: url({{ customfilepath('add.png') }}) no-repeat left center;
  margin: 0 10px 0 0;
}

/* ------------------- Messages --------------------------- */

#messages {
  padding: 20px 0 5px;
  margin: 0 auto;
}
.featured #messages {
  background: #f0f0f0;
  background: rgba(30, 50, 10, 0.08);
}
div.messages {
  margin: 8px 15px;
}

/* ------------------- Breadcrumbs ------------------------ */

.breadcrumb {
  font-size: 0.929em;
  padding: 10px;
}

.breadcrumb a {
  padding: 12px 0;
}

/* ------------------- User Profile ----------------------- */

.profile .user-picture {
  float: none;
}

/* ------------------- Password Meter --------------------- */

.confirm-parent,
.password-parent {
  width: 34em;
}
.password-parent,
div.form-item div.password-suggestions {
  position: relative;
}
.password-strength-text,
.password-strength-title,
div.password-confirm {
  font-size: 0.82em;
}
.password-strength-text {
  margin-top: 0.2em;
}
div.password-confirm {
  margin-top: 2.2em;
  width: 20.73em;
}

/* ------------------- Buttons ---------------------------- */

input.form-submit,
a.button {
  background: #fff url({{ customfilepath('buttons.png') }}) 0 0 repeat-x;
  border: 1px solid #e4e4e4;
  border-bottom: 1px solid #b4b4b4;
  border-left-color: #d2d2d2;
  border-right-color: #d2d2d2;
  color: #3a3a3a;
  cursor: pointer;
  font-size: 0.929em;
  font-weight: normal;
  text-align: center;
  margin-bottom: 1em;
  margin-right: 0.6em; /* LTR */
  padding: 4px 17px;
  border-radius: 15px;
}
a.button:link,
a.button:visited,
a.button:hover,
a.button:focus,
a.button:active {
  text-decoration: none;
  color: #5a5a5a;
}

/* ------------------- Form Elements ---------------------- */

fieldset {
  background: #ffffff;
  border: 1px solid #cccccc;
  margin-top: 10px;
  margin-bottom: 32px;
  padding: 0 0 10px;
  position: relative;
  top: 12px; /* Offsets the negative margin of legends */
  border-radius: 4px;
}
.fieldset-wrapper {
  margin-top: 25px;
}
.node-form .vertical-tabs .fieldset-wrapper {
  margin-top: 0;
}
.filter-wrapper {
  top: 0;
  padding: 1em 0 0.2em;
  border-top-left-radius: 0;
  border-top-right-radius: 0;
}
.filter-help a {
  font-size: 0.857em;
  padding: 2px 20px 0;
}
.filter-wrapper .form-item label {
  margin-right: 10px;
}
.filter-wrapper .form-item {
  padding: 0 0 0.5em 0.5em;
}
.filter-guidelines {
  padding: 0 1.5em 0 0.5em;
}
fieldset.collapsed {
  background: transparent;
  border-radius: 0;
}
fieldset legend {
  background: #dbdbdb;
  border: 1px solid #ccc;
  border-bottom: none;
  color: #3b3b3b;
  display: block;
  height: 2em;
  left: -1px; /* LTR */
  font-family: "Lucida Grande", "Lucida Sans Unicode", Verdana, sans-serif;
  line-height: 2;
  padding: 0;
  position: absolute;
  text-indent: 10px;
  text-shadow: 0 1px 0 #fff;
  top: -12px;
  width: 100%;
  border-top-left-radius: 4px;
  border-top-right-radius: 4px;
}
fieldset.collapsed legend {
  border-radius: 4px;
}
fieldset legend a {
  color: #3b3b3b;
}
fieldset legend a:hover,
fieldset legend a:focus,
fieldset legend a:active {
  color: #000;
}
fieldset .fieldset-wrapper {
  padding: 0 10px;
}
fieldset .fieldset-description {
  margin-top: 5px;
  margin-bottom: 1em;
  line-height: 1.4;
  color: #3c3c3c;
  font-style: italic;
}
input {
  margin: 2px 0;
  padding: 4px;
}
input,
textarea {
  font-size: 0.929em;
}
textarea {
  line-height: 1.5;
}
textarea.form-textarea,
select.form-select {
  padding: 4px;
}
input.form-text,
input.form-tel,
input.form-email,
input.form-url,
input.form-search,
input.form-number,
input.form-color,
textarea.form-textarea,
select.form-select {
  border: 1px solid #ccc;
}
input.form-submit:hover,
input.form-submit:focus {
  background: #dedede;
}
.password-suggestions ul li {
  margin-left: 1.2em; /* LTR */
}
.form-item {
  margin-bottom: 1em;
  margin-top: 2px;
}
.form-item label {
  font-size: 0.929em;
}
.form-type-radio label,
.form-type-checkbox label {
  margin-left: 4px;
}
.form-type-radio .description,
.form-type-checkbox .description {
  margin-left: 2px;
}
.form-actions {
  padding-top: 10px;
}
/* Contact Form */
.contact-form #edit-name {
  width: 75%;
  border-radius: 4px;
}
.contact-form #edit-mail {
  width: 75%;
  border-radius: 4px;
}
.contact-form #edit-subject {
  width: 75%;
  border-radius: 4px;
}
.contact-form #edit-message {
  width: 76.3%;
  border-top-left-radius: 4px;
  border-top-right-radius: 4px;
}
.contact-form .resizable-textarea .grippie {
  width: 76%;
  border-bottom-left-radius: 4px;
  border-bottom-right-radius: 4px;
}

/* ------------------- Disabled Form Elements ------------- */
input.form-button-disabled,
input.form-button-disabled:hover,
input.form-button-disabled:focus,
input.form-button-disabled:active,
.form-disabled input,
.form-disabled select,
.form-disabled textarea {
  background: #ededed;
  border-color: #bbb;
  color: #717171;
}
.form-disabled label {
  color: #717171;
}

/* ------------------- Animated Throbber ------------------ */
.js input.form-autocomplete {
  background-position: 100% 4px; /* LTR */
}
.js input.throbbing {
  background-position: 100% -16px; /* LTR */
}

/* ------------------- Comment Form ----------------------- */
.comment-form label {
  float: left; /* LTR */
  font-size: 0.929em;
  width: 120px;
}
.comment-form input,
.comment-form .form-select {
  margin: 0;
  border-radius: 4px;
}
.comment-form .form-type-textarea label {
  float: none;
}
.comment-form .form-item,
.comment-form .form-radios,
.comment-form .form-type-checkbox,
.comment-form .form-select {
  margin-bottom: 10px;
  overflow: hidden;
}
.comment-form .form-type-checkbox,
.comment-form .form-radios {
  margin-left: 120px; /* LTR */
}
.comment-form .form-type-checkbox label,
.comment-form .form-radios label {
  float: none;
  margin-top: 0;
}
.comment-form input.form-file {
  width: auto;
}
.no-sidebars .comment-form .form-text {
  width: 800px;
}
.one-sidebar .comment-form .form-text {
  width: 500px;
}
.two-sidebars .comment-form .form-text {
  width: 320px;
}
.comment-form .form-item .description {
  font-size: 0.786em;
  line-height: 1.2;
  margin-left: 120px; /* LTR */
}
#content h2.comment-form {
  margin-bottom: 0.5em;
}
.comment-form .form-textarea {
  border-top-left-radius: 4px;
  border-top-right-radius: 4px;
}
.comment-form fieldset.filter-wrapper .fieldset-wrapper,
.comment-form .text-format-wrapper .form-item {
  margin-top: 0;
  margin-bottom: 0;
}
.filter-wrapper label {
  width: auto;
  float: none;
}
.filter-wrapper .form-select {
  min-width: 120px;
}
.comment-form fieldset.filter-wrapper .tips {
  font-size: 0.786em;
}
#comment-body-add-more-wrapper .form-type-textarea label {
  margin-bottom: 0.4em;
}
#edit-actions input {
  margin-right: 0.6em; /* LTR */
}

/* ------------------- Other Overrides -------------------- */

div.password-suggestions {
  border: 0;
}
.ui-widget-overlay {
  background: #222222;
  opacity: 0.7;
}
div.vertical-tabs .vertical-tabs-panes fieldset.vertical-tabs-pane {
  padding: 1em;
}
#forum .name {
  font-size: 1.083em;
}
#forum .description {
  font-size: 1em;
}

/* ------------------- Search Form ------------------------ */

#block-search-form {
  padding-bottom: 7px;
}
#block-search-form .content {
  margin-top: 0;
}
#search-form input[type="search"],
#block-search-form input[type="search"] {
  box-sizing: border-box;
  padding: 4px;
  -webkit-appearance: textfield;
}
#search-form input[type="search"]::-webkit-search-decoration,
#block-search-form input[type="search"]::-webkit-search-decoration {
  display: none;
}
#search-form input#edit-keys,
#block-search-form .form-item-search-block-form input {
  float: left; /* LTR */
  font-size: 1em;
  margin-right: 5px;
  width: 9em;
}
#search-block-form input.form-submit,
#search-form input.form-submit {
  margin-left: 0;
  margin-right: 0;
  height: 25px;
  width: 34px;
  padding: 0;
  cursor: pointer;
  text-indent: -9999px;
  border-color: #e4e4e4 #d2d2d2 #b4b4b4;
  background: url({{ customfilepath('search-button.png') }}) no-repeat center top;
  overflow: hidden;
}
#search-block-form input.form-submit:hover,
#search-block-form input.form-submit:focus,
#search-form input.form-submit:hover,
#search-form input.form-submit:focus {
  background-position: center bottom;
}
#search-form .form-item-keys label {
  display: block;
}

/* ------------------- Search Results --------------------- */
ol.search-results {
  padding-left: 0;
}
.search-results li {
  border-bottom: 1px solid #d3d7d9;
  padding-bottom: 0.4285em;
  margin-bottom: 0.5em;
}
.search-results li:last-child {
  border-bottom: none;
  padding-bottom: 0;
  margin-bottom: 1em;
}
.search-results .search-snippet-info {
  padding-left: 0;
}

/* ------------------- Shortcut Links --------------------- */

.shortcut-wrapper {
  margin: 2.2em 0 1.1em 0; /* Same as usual h1#page-title margin. */
}
.shortcut-wrapper h1#page-title {
  float: left; /* LTR */
  margin: 0;
}
div.add-or-remove-shortcuts {
  padding-top: 0.9em;
}
.overlay div.add-or-remove-shortcuts {
  padding-top: 0.8em;
}

/* ------------------- Admin-specific Theming ------------- */

.page-admin #content img {
  margin-right: 15px; /* LTR */
}
.page-admin #content .simpletest-image img {
  margin: 0;
}
.page-admin-structure-block-demo .block-region {
  background: #ffff66;
  border: 1px dotted #9f9e00;
  color: #000;
  font: 90% "Lucida Grande", "Lucida Sans Unicode", sans-serif;
  margin: 5px;
  padding: 5px;
  text-align: center;
  text-shadow: none;
}
.page-admin-structure-block-demo #featured .block-region {
  font-size: 0.55em;
}
.page-admin-structure-block-demo #header .block-region {
  width: 500px;
}
.page-admin #admin-dblog img {
  margin: 0 5px;
}
/* Fix spacing when Seven is used in the overlay. */
#system-theme-settings fieldset {
  padding: 0;
}
#system-theme-settings fieldset .fieldset-legend {
  margin-top: 0;
}
/* Configuration. */
div.admin .right,
div.admin .left {
  width: 49%;
  margin: 0;
}
div.admin-panel {
  background: #fbfbfb;
  border: 1px solid #ccc;
  margin: 10px 0;
  padding: 0 5px 5px;
}
div.admin-panel h3 {
  margin: 16px 7px;
}
div.admin-panel dt {
  border-top: 1px solid #ccc;
  padding: 7px 0 0;
}
div.admin-panel dd {
  margin: 0 0 10px;
}
div.admin-panel .description {
  margin: 0 0 14px 7px;
}

/* ------------------- Overlay Layout Styles -------------- */

.overlay #main,
.overlay #content {
  width: auto;
  float: none;
}
.overlay #page {
  padding: 0 2em;
}
.overlay .region-page-top,
.overlay #header,
.overlay #page-title,
.overlay #featured,
.overlay #sidebar-first,
.overlay #triptych-wrapper,
.overlay #footer-wrapper {
  display: none;
}
.overlay-processed .field-type-image {
  display: block;
  float: none;
}
.overlay #messages {
  width: auto;
}

/* ------------------- Poll ------------------------------- */

.node .poll {
  margin: 2em 0;
}
.node .poll #edit-choice {
  margin: 0 0 1.5em;
}
.poll .vote-form {
  text-align: left; /* LTR */
  margin: 0;
}
.poll .percent {
  font-size: 0.857em;
  font-style: italic;
  margin-bottom: 3em;
  margin-top: -3.2em;
  float: right; /* LTR */
  text-align: right; /* LTR */
}
.poll .choice-title {
  clear: right; /* LTR */
}
.poll .total {
  font-size: 0.929em;
  font-style: italic;
  text-align: right; /* LTR */
  clear: both;
}
.node .poll {
  margin: 1.8em 0 0;
}
.node .poll .text {
  margin-right: 6.75em;
}
.node .poll #edit-choice {
  margin: 0 0 1.2em;
}
.poll .bar .foreground {
  background-color: #666;
}
#footer-wrapper .poll .bar {
  background-color: #666;
}
#footer-wrapper .poll .bar .foreground {
  background-color: #ddd;
}

/* ------------------- Book ------------------------------- */
.book-navigation .menu {
  border-top: 1px solid #d6d6d6;
}
.book-navigation .book-pager {
  border-bottom: 1px solid #d6d6d6;
  border-top: 1px solid #d6d6d6;
  margin: 0;
}

/* ------------------- Menu Toggle Link ------------------- */
a#menu-toggle {
  display:none;
  background: none repeat scroll 0 0 rgba(255, 255, 255, 0.7);
  padding: 0.7em 0 0.7em 10px;
  text-decoration: none;
  text-shadow: 0 1px #EEEEEE;
  position:relative;
}

a#menu-toggle:after {
  content:"";
  background: url('../images/toggle.png') no-repeat;
  width: 22px;
  height: 30px;
  display: inline-block;
  position: absolute;
  right: 10px;
}

/* ------------------- Media Queries ---------------------- */

@media all and (max-width: 460px) {
  /* ----------------- Menu on Small Resolutions ---------- */
  a#menu-toggle {
    display:block;
  }

  #main-menu-links {
    display: none;
    height: auto;
  }
  
  /* ----------------- Forms on Small Screens ------------- */
  input.form-text,
  input.form-tel,
  input.form-email, 
  input.form-url,
  input.form-search,
  input.form-number, 
  input.form-color,
  textarea.form-textarea,
  select.form-select {
    width: 100%;
  }
}

@media all and (min-width: 461px) and (max-width: 900px) {
 /* ------------------ Header and Menus ------------------- */

 .region-header {
    margin: .5em 5px .75em;
  }
  #logo {
    padding: 5px 0 0 5px; /* LTR */
  }
  #name-and-slogan {
    padding: 10px 10px 8px;
  }
  #main-menu-links {
    margin: 0 5px;
    padding: 0;
    text-align: center;
  }
  #main-menu-links li {
    float: left;
    margin-right: 5px;
    padding: 0;
    display: inline-block;
    width: 32.75%;
  }
  #main-menu-links li:nth-child(3n) {
    margin-right: -5px; /* LTR */
  }
  #main-menu-links a {
    float: none;
    display: block;
    border-radius: 8px;
    margin-bottom: 5px;
    padding: 0.9em 5px;
  }
  #featured {
    font-size: 1.43em;
  }
  #featured h2 {
    font-size: 1.174em;
  }
  #triptych h2 {
    font-size: 1.243em;
    margin-bottom: 0.9em;
  }
}

@media all and (min-width: 901px) {

  .region-header {
    margin: 1em 5px 1.5em;
  }
  #logo {
    padding: 15px 15px 15px 10px; /* LTR */
  }
  #name-and-slogan {
    padding: 26px 0 0;
    margin: 0 0 30px 15px; /* LTR */
  }
  #site-name {
    font-size: 1.821em;
  }
  #main-menu-links {
    font-size: 0.929em;
    margin: 0;
    padding: 0 15px;
  }
  #main-menu-links li {
    float: left; /* LTR */
    list-style: none;
    padding: 0 1px;
    margin: 0 1px;
    width: auto;
  }
  #main-menu-links a {
    float: left; /* LTR */
    padding: 0.7em 0.8em;
    margin-bottom: 0;
    border-bottom-left-radius: 0;
    border-bottom-right-radius: 0;
  }
  #featured {
    font-size: 1.643em;
    line-height: 1.4;

  }
  #featured h2 {
    font-size: 1.174em;
    line-height: 1;
  }
  .featured #main-menu-links li a:active,
  .featured #main-menu-links li a.active {
    background: #f0f0f0;
    background: rgba(240, 240, 240, 1.0);
  }
}


/* ------------------- Misc Fixes ------------------------- */
.element-invisible {
  position: absolute !important;
  clip: rect(1px, 1px, 1px, 1px);
  left: 0;
}