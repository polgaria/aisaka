import subprocess, os, sphinxjp.themes.basicstrap
 
project = "aisaka"
copyright = "2019, geni"
author = "geni"

extensions = ["breathe", "sphinxjp.themes.basicstrap"]

html_theme = "basicstrap"
html_theme_options = {
    'inner_theme': True,
    'inner_theme_name': 'bootswatch-darkly',
}

def configureDoxyfile(input_dir, output_dir):
    with open("Doxyfile.in", "r") as file :
        filedata = file.read()
 
    filedata = filedata.replace("@DOXYGEN_INPUT_DIR@", input_dir)
    filedata = filedata.replace("@DOXYGEN_OUTPUT_DIR@", output_dir)
 
    with open("Doxyfile", "w") as file:
        file.write(filedata)
 
# Check if we"re running on Read the Docs" servers
read_the_docs_build = os.environ.get("READTHEDOCS", None) == "True"

breathe_default_project = "aisaka"
breathe_projects = {}
 
if read_the_docs_build:
    input_dir = "../include/aisaka/"
    output_dir = "build"
    configureDoxyfile(input_dir, output_dir)
    subprocess.call("doxygen", shell=True)
    breathe_projects["aisaka"] = output_dir + "/xml"