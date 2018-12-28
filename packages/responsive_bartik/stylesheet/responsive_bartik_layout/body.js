/* ------------------- Basic Layout Styles ---------------- */

html,
body,
#page  {
  height: 100%;
}
#page-wrapper {
  min-height: 100%;
}
#header div.section,
#featured div.section,
#messages div.section,
#main,
#triptych,
#footer-columns,
#footer {
  width: 100%;
  max-width: 860px;
  margin-left: auto;
  margin-right: auto;
}
#header div.section {
  position: relative;
}
.region-header {
  float: right; /* LTR */
  margin: 1em 5px 1.5em;
}
#secondary-menu {
  margin: 0 auto;
  overflow: hidden;
  width: 100%;
}
#main-wrapper {
  min-height: 300px;
}
#content .section,
.sidebar .section {
  padding: 0 15px;
}
#breadcrumb {
  margin: 0 15px;
}
#footer-wrapper {
  padding: 35px 0 30px;
}
#footer-wrapper .section {
  -moz-box-sizing: border-box;
  box-sizing: border-box;
  padding: 0 15px;
}
.region-triptych-first,
.region-triptych-middle,
.region-triptych-last {
  -moz-box-sizing: border-box;
  box-sizing: border-box;
  padding: 0 20px 0;
}
.region-footer-firstcolumn,
.region-footer-secondcolumn,
.region-footer-thirdcolumn,
.region-footer-fourthcolumn {
  -moz-box-sizing: border-box;
  box-sizing: border-box;
  padding: 0 10px;
}

@media all and (min-width: 560px) and (max-width: 850px) {

  #sidebar-first,
  .region-triptych-first,
  .region-triptych-middle,
  .region-triptych-last,
  .region-footer-firstcolumn,
  .region-footer-secondcolumn,
  .region-footer-thirdcolumn,
  .region-footer-fourthcolumn {
    display: inline;
    float: left; /* LTR */
    position: relative;
  }
  #sidebar-first,
  #sidebar-second {
    width: 50%;
  }
  #sidebar-second {
    margin-left: 50%; /* LTR */
  }
  .one-sidebar #sidebar-first,
  .one-sidebar #sidebar-second {
    width: 100%;
  }
  .one-sidebar #sidebar-second {
    margin-left: 0; /* LTR */
  }
  .region-triptych-first,
  .region-triptych-middle,
  .region-triptych-last {
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    padding: 0 10px 0;
    width: 33%;
  }
  .region-footer-firstcolumn,
  .region-footer-secondcolumn {
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    padding: 0 10px;
    width: 50%;
  }
  .region-footer-thirdcolumn,
  .region-footer-fourthcolumn {
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    padding: 0 10px;
    width: 50%;
  }
  .region-footer-thirdcolumn {
    clear: both;
  }
}

@media all and (min-width: 851px) {

  #header div.section,
  #featured div.section,
  #messages div.section,
  #main,
  #triptych,
  #footer-columns,
  #footer {
    max-width: 1290px;
  }
  #content,
  #sidebar-first,
  #sidebar-second,
  .region-triptych-first,
  .region-triptych-middle,
  .region-triptych-last,
  .region-footer-firstcolumn,
  .region-footer-secondcolumn,
  .region-footer-thirdcolumn,
  .region-footer-fourthcolumn {
    display: inline;
    float: left; /* LTR */
    position: relative;
  }
  .two-sidebars #content {
    margin-left: 25%;
    margin-right: 25%;
    width: 50%;
  }
  .one-sidebar #content {
    width: 75%;
  }
  .no-sidebars #content {
    width: 100%;
  }
  .sidebar-first #content {
    margin-left: 25%; /* LTR */
    margin-right: 0; /* LTR */
  }
  .sidebar-second #content {
    margin-right: 25%; /* LTR */
    margin-left: 0; /* LTR */
  }
  #sidebar-first {
    width: 25%;
    margin-left: -100%; /* LTR */
  }
  #sidebar-second {
    width: 25%;
    margin-left: -25%; /* LTR */
    clear: none;
  }
  .region-triptych-first,
  .region-triptych-middle,
  .region-triptych-last {
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    width: 33%;
  }
  .region-footer-firstcolumn,
  .region-footer-secondcolumn,
  .region-footer-thirdcolumn,
  .region-footer-fourthcolumn {
    -moz-box-sizing: border-box;
    box-sizing: border-box;
    padding: 0 10px;
    width: 25%;
  }
}