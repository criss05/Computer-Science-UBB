document.addEventListener('DOMContentLoaded', () =>{
    const form = document.querySelector('form');

    form.addEventListener('submit', async (event)=>{
        event.preventDefault();

        const formData = new FormData(form);
        const name = formData.get("name");

        if (name){
            window.location.href = `home_page.php?name=${name}`;
        }
        else{
            alert("Please enter the name");
        }
    });
});