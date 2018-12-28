<div id="messages">

</div>
<div id="layout-test">
  <h2>Layout Tests</h2>
  <script>
    QUnit.test("Layout Basics Tests", function (assert) {
      assert.equal('', 'preprocess var val', 'Layout preprocessing is functioning properly.');
      assert.ok(jQuery('head meta#layout-custom-head-test').length, 'Layout custom HTML Head is being added properly.');
      assert.ok('', 'Layout title variable exists');
      assert.ok('', 'Layout object is available to twig.');
      assert.ok($('#layout-content').html(), 'Layout content is populated.');
      assert.equal($('head title').text(), '', 'Page title is being formatted properly.');
      assert.ok($('#layout-admin-notes div').html(), 'The layout admin notes are set and output correctly.');
      assert.equal('', 'catalyst_test_1x', 'This layout is apart of the catalyst_test_1x package.');
      assert.equal('', '1', 'This layout is set to internal.');
      assert.equal('0', '0', 'Drupal processing is disabled for this layout.');
    });
    QUnit.test("Layout JS Tests", function (assert) {
      assert.notEqual(typeof layout_custom_js_var, 'undefined', 'Layout Custom Javascript Test');
      assert.notEqual(typeof layout_shared_js_var, 'undefined', 'Layout Shared Javascript Test');
      assert.notEqual(typeof layout_remote_js_var, 'undefined', 'Layout Remote Javascript Test');
      assert.notEqual(typeof layout_local_js_var, 'undefined', 'Layout Local Javascript Test');
      assert.notEqual(typeof layout_footer_js_var, 'undefined', 'Layout Footer Javascript Test');
    });
  </script>
  <h3>Layout CSS Tests</h3>
  <ul>
    <li class="layout-custom-css-test">This should have a <strong>solid</strong> border.</li>
    <li class="layout-shared-css-test">This should have a <strong>double</strong> border.</li>
    <li class="layout-remote-css-test">This should have a <strong>dotted</strong> border.</li>
    <li class="layout-local-css-test">This should have a <strong>dashed</strong> border.</li>
  </ul>
  <script>
    QUnit.test("Layout CSS Tests", function (assert) {
      assert.equal(jQuery('.layout-custom-css-test').css('border-top-style'), 'solid', 'Layout Custom CSS Test');
      assert.equal(jQuery('.layout-shared-css-test').css('border-top-style'), 'double', 'Layout Shared CSS Test');
      assert.equal(jQuery('.layout-local-css-test').css('border-top-style'), 'dashed', 'Layout Local CSS Test');
      assert.equal(jQuery('.layout-remote-css-test').css('border-top-style'), 'dotted', 'Layout Remote CSS Test');
    });
  </script>
  <h3>Layout Files Tests</h3>
  <strong>Custom file test:</strong>
  <ul>
    <li>Test <em>custom</em> file PATH: <strong>/sites/dev-catalyst.dd/files/media/layout/catalyst_test_layout_1/layout-custom-test.png</strong></li>
    <li>Test <em>custom</em> file URL: <strong>public://media/layout/catalyst_test_layout_1/layout-custom-test.png</strong></li>
    <li>Test <em>custom</em> file as image:<br /><img id="layout-custom-file-test" src="/sites/dev-catalyst.dd/files/media/layout/catalyst_test_layout_1/layout-custom-test.png" /></li>
  </ul>
  <strong>Shared file test:</strong>
  <ul>
    <li>Test <em>shared</em> file PATH: <strong></strong></li>
    <li>Test <em>shared</em> file URL: <strong></strong></li>
    <li>Test <em>shared</em> file as image:<br /><img id="layout-shared-file-test" src="" /></li>
  </ul>
  <strong>Local file test:</strong>
  <ul>
    <li>Test <em>local</em> file PATH: <strong></strong></li>
    <li>Test <em>local</em> file URL: <strong></strong></li>
    <li>Test <em>local</em> file as image:<br /><img id="layout-local-file-test" src="" /></li>
  </ul>
  <strong>Remote file test:</strong>
  <ul>
    <li>Test <em>remote</em> file PATH: <strong></strong></li>
    <li>Test <em>remote</em> file URL: <strong></strong></li>
    <li>Test <em>remote</em> file as image:<br /><img id="layout-remote-file-test" src="" /></li>
  </ul>
  <script>
  QUnit.test("Layout Files Tests", function (assert) {
    var layoutCustomFileImg = jQuery('img#layout-custom-file-test');
    assert.ok(layoutCustomFileImg.attr('src'), 'Layout Custom File Data Test');
    assert.equal(layoutCustomFileImg.width(), 401, 'Layout Custom File Exists Test');
    var layoutSharedFileImg = jQuery('img#layout-shared-file-test');
    assert.ok(layoutSharedFileImg.attr('src'), 'Layout Shared File Data Test');
    assert.equal(layoutSharedFileImg.width(), 301, 'Layout Shared File Exists Test');
    var layoutLocalFileImg = jQuery('img#layout-local-file-test');
    assert.ok(layoutLocalFileImg.attr('src'), 'Layout Local File Data Test');
    assert.equal(layoutLocalFileImg.width(), 201, 'Layout Local File Exists Test');
    var layoutRemoteFileImg = jQuery('img#layout-remote-file-test');
    assert.ok(layoutRemoteFileImg.attr('src'), 'Layout Remote File Data Test');
    assert.equal(layoutRemoteFileImg.width(), 101, 'Layout Remote File Exists Test');
  });
  </script>
  <h3>Layout Block Tests</h3>
  
    <script>
  QUnit.test("Layout Block Tests", function (assert) {
    assert.ok(jQuery('#layout-embedded-block').length, 'Layout Embedded Block Embedded Test');
    assert.ok(jQuery('#layout-test-region #layout-region-block').length, 'Layout Region Block Embedded Test');
  });
  </script>
  <div id="layout-content"></div>
    <h2>Leaf Block Tests</h2>
  
    <script>
  QUnit.test("Leaf Block Tests", function (assert) {
    assert.ok(jQuery('#embedded-block').length, 'Leaf Embedded Block Embedded Test');
    assert.ok(jQuery('#block-test-region #region-block').length, 'Leaf Region Block Embedded Test');
  });
  </script>
</div>
<hr />
<div id="layout-info">
  <div id="layout-label"><label>Label:</label><span><a href="/admin/catalyst/layout/?destination=devel/php"></a> ()</span></div>
  <div id="layout-machine"><label>Machine:</label><span></span></div>
  <div id="layout-admin-notes"><label>Readme:</label><div></div></div>
</div>
<hr />