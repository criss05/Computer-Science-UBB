async function loadAllProjects(){
    try{
        const response = await fetch("../api/projects.php");
        const data = await response.json();
        const homePage = document.getElementById('homePageDiv');
        homePage.innerHTML = '';

        if (data.error){
            homePage.innerHTML = `<p>${data.error}</p>`;
            return;
        }
        
        data.forEach(element => {
            const projectDetails = document.createElement('div');
            projectDetails.innerHTML = `
            <h2>${element.name}</h2>
            <p><strong>Project manager id:</strong>${element.project_manager_id}</p>
            <p><strong>Description:</strong>${element.description}</p>
            <p><strong>Members:</strong>${element.members}</p>
            <br>`

            homePage.appendChild(projectDetails);
        });
        
    }
    catch(error){
        console.error('Error fetching the projects details: ', error);
        viewAllProjects.innerHTML = '<p>Error loading the projects.</p>';
    }
}

async function loadMyProjects(developerName){
     try{
        const response = await fetch("../api/projects.php");
        const data = await response.json();
        const homePage = document.getElementById('homePageDiv');
        homePage.innerHTML = '';

        if (data.error){
            homePage.innerHTML = `<p>${data.error}</p>`;
            return;
        }
        
        data.forEach(element => {
            if((element.members).includes(developerName.toLowerCase())){
                const projectDetails = document.createElement('div');
                projectDetails.innerHTML = `
                <h2>${element.name}</h2>
                <br>`

                homePage.appendChild(projectDetails);
            }
        });
        
    }
    catch(error){
        console.error('Error fetching the projects details: ', error);
        viewAllProjects.innerHTML = '<p>Error loading the projects.</p>';
    }
}

async function loadDevelopers(){
     try{
        const response = await fetch("../api/developers.php");
        const data = await response.json();
        const homePage = document.getElementById('homePageDiv');
        homePage.innerHTML = `<br><input id="skillInput" type="text" placeholder="Skill..."></input>
                            <div id="developers"></div>`;

        if (data.error){
            homePage.innerHTML = `<p>${data.error}</p>`;
            return;
        }
        
        const inputField = document.getElementById("skillInput");
        const resultDiv = document.getElementById("developers");

        inputField.addEventListener('input', () => {
            const filterValue = inputField.value.toLowerCase();
            resultDiv.innerHTML='';
            
            const filtered = data.filter(dev => 
                dev.skills.toLowerCase().includes(filterValue) || filterValue === ""
            );

            filtered.forEach(element => {
                const projectDetails = document.createElement('div');
                projectDetails.innerHTML = `
                <h2>${element.name}</h2>
                <p><strong>Age:</strong>${element.age}</p>
                <p><strong>Skill:</strong>${element.skills}</p>
                <br>`

                resultDiv.appendChild(projectDetails);
            });
        })
        
    }
    catch(error){
        console.error('Error fetching the projects details: ', error);
        viewAllProjects.innerHTML = '<p>Error loading the projects.</p>';
    }
}


document.addEventListener('DOMContentLoaded', async () =>{
    const urlParams = new URLSearchParams(window.location.search);
    const developerName = urlParams.get('name');

    if (!developerName){
        window.location.href('start.php');
    }

    const viewAllProjects = document.getElementById('viewAllProjects');
    viewAllProjects.addEventListener("click", () =>{
        loadAllProjects();
    });

    const viewMyProjects = document.getElementById('viewMyProjects');
    viewMyProjects.addEventListener("click", () =>{
        loadMyProjects(developerName);
    });

    const viewDevelopers = document.getElementById('viewAllDevelopers');
    viewDevelopers.addEventListener("click", () =>{
        loadDevelopers();
    });

    const addDevelopers = document.getElementById('addDevelopers');
    addDevelopers.addEventListener("click", () =>{
        window.location.href = `add_developers.php`;
    });
});