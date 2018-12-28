<h2>Region Block Tests</h2>
<h3 id="embedded-block">This is a manually embedded block.</h3>
<p>This block has it's own files, css, javascipt, and processing.</p>
<h3>Embedded Block CSS Tests</h3>
<ul><li class="block-embed-custom-css-test">This should have a <strong>solid</strong> border.</li>
  <li class="block-embed-shared-css-test">This should have a <strong>double</strong> border.</li>
  <li class="block-embed-remote-css-test">This should have a <strong>dotted</strong> border.</li>
  <li class="block-embed-local-css-test">This should have a <strong>dashed</strong> border.</li>
</ul><script>
<!--//--><![CDATA[// ><!--

  QUnit.test("Embedded Block CSS Tests", function (assert) {
    assert.equal(jQuery('.block-embed-custom-css-test').css('border-top-style'), 'solid', 'Embedded Block Custom CSS Test');
    assert.equal(jQuery('.block-embed-shared-css-test').css('border-top-style'), 'double', 'Embedded Block Shared CSS Test');
    assert.equal(jQuery('.block-embed-local-css-test').css('border-top-style'), 'dashed', 'Embedded Block Local CSS Test');
    assert.equal(jQuery('.block-embed-remote-css-test').css('border-top-style'), 'dotted', 'Embedded Block Remote CSS Test');
  });

//--><!]]>
</script><h3>Embedded Block Files Tests</h3>
<strong>Custom file test:</strong>
<ul><li>Test <em>custom</em> file PATH: <strong>/sites/dev-catalyst.dd/files/media/block/%5Bfield__machine%5D/block-embed-custom-test_3.png</strong></li>
  <li>Test <em>custom</em> file URL: <strong>public://media/block/[field__machine]/block-embed-custom-test_3.png</strong></li>
  <li>Test <em>custom</em> file as image:<br /><img id="block-embed-custom-file-test" src="/sites/dev-catalyst.dd/files/media/block/%5Bfield__machine%5D/block-embed-custom-test_3.png" /></li>
</ul><strong>Shared file test:</strong>
<ul><li>Test <em>shared</em> file PATH: <strong></strong></li>
  <li>Test <em>shared</em> file URL: <strong></strong></li>
  <li>Test <em>shared</em> file as image:<br /><img id="block-embed-shared-file-test" src="" /></li>
</ul><strong>Local file test:</strong>
<ul><li>Test <em>local</em> file PATH: <strong></strong></li>
  <li>Test <em>local</em> file URL: <strong></strong></li>
  <li>Test <em>local</em> file as image:<br /><img id="block-embed-local-file-test" src="" /></li>
</ul><strong>Remote file test:</strong>
<ul><li>Test <em>remote</em> file PATH: <strong></strong></li>
  <li>Test <em>remote</em> file URL: <strong></strong></li>
  <li>Test <em>remote</em> file as image:<br /><img id="block-embed-remote-file-test" src="" /></li>
</ul><script>
<!--//--><![CDATA[// ><!--

QUnit.test("Embedded Block Tests", function (assert) {
  assert.ok('', 'Block "title" variable Test');
  assert.equal('', 'embedded block var val', 'Embedded Block Processing Test');
});  
QUnit.test("Embedded Block Javascript Tests", function (assert) {
  assert.notEqual(typeof block_embed_custom_js_var, 'undefined', 'Embedded Block Custom Javascript Test');
  assert.notEqual(typeof block_embed_shared_js_var, 'undefined', 'Embedded Block Shared Javascript Test');
  assert.notEqual(typeof block_embed_remote_js_var, 'undefined', 'Embedded Block Remote Javascript Test');
  assert.notEqual(typeof block_embed_local_js_var, 'undefined', 'Embedded Block Local Javascript Test');
  assert.notEqual(typeof block_embed_footer_js_var, 'undefined', 'Embedded Block Footer Javascript Test');
});
QUnit.test("Embedded Block Files Tests", function (assert) {
  var blockEmbedCustomFileImg = jQuery('img#block-embed-custom-file-test');
  assert.ok(blockEmbedCustomFileImg.attr('src'), 'Embedded Block Custom File Data Test');
  assert.equal(blockEmbedCustomFileImg.width(), 410, 'Embedded Block Custom File Exists Test');
  var blockEmbedSharedFileImg = jQuery('img#block-embed-shared-file-test');
  assert.ok(blockEmbedSharedFileImg.attr('src'), 'Embedded Block Shared File Data Test');
  assert.equal(blockEmbedSharedFileImg.width(), 310, 'Embedded Block Shared File Exists Test');
  var blockEmbedLocalFileImg = jQuery('img#block-embed-local-file-test');
  assert.ok(blockEmbedLocalFileImg.attr('src'), 'Embedded Block Local File Data Test');
  assert.equal(blockEmbedLocalFileImg.width(), 210, 'Embedded Block Local File Exists Test');
  var blockEmbedRemoteFileImg = jQuery('img#block-embed-remote-file-test');
  assert.ok(blockEmbedRemoteFileImg.attr('src'), 'Embedded Block Remote File Data Test');
  assert.equal(blockEmbedRemoteFileImg.width(), 110, 'Embedded Block Remote File Exists Test');
});

//--><!]]>
</script>