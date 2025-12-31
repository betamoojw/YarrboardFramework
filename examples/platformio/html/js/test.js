$(function () {
  $("#controlPage").html(`
    <h1>Hello World</h1>
    <p>Edit js/test.js to modify the example</p>
  `);

  //example page handler.
  YB.App.onPageOpen("stats", function () {
    console.log("Stats Page Opened");
    return true;
  })
});