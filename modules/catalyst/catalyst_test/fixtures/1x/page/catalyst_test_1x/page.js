<h2>Page Tests</h2>
<script>
<!--//--><![CDATA[// ><!--

  QUnit.test("Page Basics Tests", function (assert) {
    assert.equal('', 'preprocess var val', 'Page Preprocessing Test');
    assert.ok(jQuery('head meta#page-custom-head-test').length, 'Page Custom HTML Head Test');
    assert.ok('', 'Page  title variable test');
    assert.equal($('#template-test').length, 1, 'Template tests loaded.');
    assert.equal($('#page-test-region #page-advanced-block').length, 1, 'Advanced block placements is functioning.');
  });
  QUnit.test("Page JS Tests", function (assert) {
    assert.notEqual(typeof page_custom_js_var, 'undefined', 'Page Custom Javascript Test');
    assert.notEqual(typeof page_shared_js_var, 'undefined', 'Page Shared Javascript Test');
    assert.notEqual(typeof page_remote_js_var, 'undefined', 'Page Remote Javascript Test');
    assert.notEqual(typeof page_local_js_var, 'undefined', 'Page Local Javascript Test');
    assert.notEqual(typeof page_footer_js_var, 'undefined', 'Page Footer Javascript Test');
  });

//--><!]]>
</script><h3>Page CSS Tests</h3>
<ul><li class="page-custom-css-test">This should have a <strong>solid</strong> border.</li>
  <li class="page-shared-css-test">This should have a <strong>double</strong> border.</li>
  <li class="page-remote-css-test">This should have a <strong>dotted</strong> border.</li>
  <li class="page-local-css-test">This should have a <strong>dashed</strong> border.</li>
</ul><script>
<!--//--><![CDATA[// ><!--

  QUnit.test("Page CSS Tests", function (assert) {
    assert.equal(jQuery('.page-custom-css-test').css('border-top-style'), 'solid', 'Page Custom CSS Test');
    assert.equal(jQuery('.page-shared-css-test').css('border-top-style'), 'double', 'Page Shared CSS Test');
    assert.equal(jQuery('.page-local-css-test').css('border-top-style'), 'dashed', 'Page Local CSS Test');
    assert.equal(jQuery('.page-remote-css-test').css('border-top-style'), 'dotted', 'Page Remote CSS Test');
  });

//--><!]]>
</script><h3>Page Files Tests</h3>
<strong>Custom file test:</strong>
<ul><li>Test <em>custom</em> file PATH: <strong>/sites/dev-catalyst.dd/files/media/page/Catalyst%20Page%20Test%20%231/page-custom-test.png</strong></li>
  <li>Test <em>custom</em> file URL: <strong>public://media/page/Catalyst Page Test #1/page-custom-test.png</strong></li>
  <li>Test <em>custom</em> file as image:<br /><img id="page-custom-file-test" src="/sites/dev-catalyst.dd/files/media/page/Catalyst%20Page%20Test%20%231/page-custom-test.png" /></li>
</ul><strong>Shared file test:</strong>
<ul><li>Test <em>shared</em> file PATH: <strong></strong></li>
  <li>Test <em>shared</em> file URL: <strong></strong></li>
  <li>Test <em>shared</em> file as image:<br /><img id="page-shared-file-test" src="" /></li>
</ul><strong>Local file test:</strong>
<ul><li>Test <em>local</em> file PATH: <strong></strong></li>
  <li>Test <em>local</em> file URL: <strong></strong></li>
  <li>Test <em>local</em> file as image:<br /><img id="page-local-file-test" src="" /></li>
</ul><strong>Remote file test:</strong>
<ul><li>Test <em>remote</em> file PATH: <strong></strong></li>
  <li>Test <em>remote</em> file URL: <strong></strong></li>
  <li>Test <em>remote</em> file as image:<br /><img id="page-remote-file-test" src="" /></li>
</ul><script>
<!--//--><![CDATA[// ><!--

QUnit.test("Page Files Tests", function (assert) {
  var pageCustomFileImg = jQuery('img#page-custom-file-test');
  assert.ok(pageCustomFileImg.attr('src'), 'Page Custom File Data Test');
  assert.equal(pageCustomFileImg.width(), 402, 'Page Custom File Exists Test');
  var pageSharedFileImg = jQuery('img#page-shared-file-test');
  assert.ok(pageSharedFileImg.attr('src'), 'Page Shared File Data Test');
  assert.equal(pageSharedFileImg.width(), 302, 'Page Shared File Exists Test');
  var pageLocalFileImg = jQuery('img#page-local-file-test');
  assert.ok(pageLocalFileImg.attr('src'), 'Page Local File Data Test');
  assert.equal(pageLocalFileImg.width(), 202, 'Page Local File Exists Test');
  var pageRemoteFileImg = jQuery('img#page-remote-file-test');
  assert.ok(pageRemoteFileImg.attr('src'), 'Page Remote File Data Test');
  assert.equal(pageRemoteFileImg.width(), 102, 'Page Remote File Exists Test');
});

//--><!]]>
</script><h3>Page Block Tests</h3>

<script>
<!--//--><![CDATA[// ><!--

  QUnit.test("Page block tests", function(assert) {
    assert.ok(jQuery('#page-embedded-block').length, 'Page Embedded Block Embedded Test');
    assert.equal(jQuery('#page-test-region #page-region-block').length, 1, 'Page Region Block Embedded Test');
  });

//--><!]]>
</script>
<hr />
<div id="page-content">
  
</div>
<hr />
<div id="json-test" class="block">
  <h3>JSON Test</h3>
  <h4 id="json-test-title"></h4>
  <p id="json-test-description"></p>
  <blockquote id="json-test-response"></blockquote>
</div>