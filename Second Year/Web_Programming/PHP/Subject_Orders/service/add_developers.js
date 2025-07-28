const projects = []

async function addProjectToList(){
    const projectInput = document.getElementById('projectInput');
    const projectName = projectInput.value;
    const projectList = document.getElementById('projectList');

    const liItem = document.createElement('li');
    liItem.innerText = projectName;

    projects.push(projectName);
    projectList.appendChild(liItem);
}

async function addDevToProject(){
    const devInput =  document.getElementById('developerInput');

    const data = {
            dev: devInput.value,
            projects: projects
        };

    try{
        await fetch("../api/projects.php", {
            method:"PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(data)
        });
    
        window.location.href = window.history.back();
    } catch (error) {
        console.error('Error updating projects:', error);
        alert('Network error while updating projects.');
    }
}

document.addEventListener("DOMContentLoaded", () =>{
    const addProject = document.getElementById("addProject");
    addProject.addEventListener("click", () => {
        addProjectToList();
    });

    const saveButton = document.getElementById("saveButton");
    saveButton.addEventListener("click", () =>{
        addDevToProject();
    });
});