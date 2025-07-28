$(document).ready(function () {
    const itemList = $("#itemList");

    let items = JSON.parse(localStorage.getItem("items")) || [];

    function renderItems(){
      itemList.empty();
      items.forEach(function(item) {
      itemList.append(`<li>${item} <button class="deleteItemButton">X</button></li>`);
    });
    }

    renderItems();

    itemList.sortable({
      update: function(){
        updateItemsArray();
      }
    });
    itemList.disableSelection();

    $("#addItemButton").click(function(){
        const item = $("#itemInput").val().trim();

        if (item){
          items.push(item);
          saveItems();
          renderItems();
          $("#itemInput").val("");
        }
        else{
          alert("please enter the item first.");
        }
    });

    itemList.on("click", ".deleteItemButton", function(){
      const index = $(this).parent().index();
      items.splice(index, 1);
      saveItems();
      renderItems();
    })

    function saveItems() {
      localStorage.setItem("items", JSON.stringify(items));
    }

    function updateItemsArray() {
      items = [];
      itemList.children("li").each(function() {
        const text = $(this).clone().children().remove().end().text().trim();
        items.push(text);
      });
      saveItems();
    }
});
  