# Developing custom GRASS tools

This is a set of Jupyter Notebooks for a workshop at FOSS4G 2022.

The workshop was created for development version of 8.3 and works with 8.2, too.

## How to run the notebooks

You do not need to install anything, the notebooks are hosted on mybinder.org.

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/wenzeslaus/foss4g-2022-developing-custom-grass-tools/main?urlpath=lab%2Ftree%2Fnotebook_1_scripts.ipynb)

If binder does not start even after couple tries, there are backup solutions below.

### Backup 1: Notebooks hosted on our server

This is for the FOSS4G workshop time only.

During a workshop, you will be given a username and a URL.
There you can login with the username and create a new password.
You should see a Jupyter Lab, so create a new Terminal from the Launcher tab and execute (use Ctrl+V to paste):

    git clone https://github.com/wenzeslaus/foss4g-2022-developing-custom-grass-tools.git
    mv foss4g-2022-developing-custom-grass-tools/* .
    rm -rf foss4g-2022-developing-custom-grass-tools/
    cp -R /data/foss4g-2022-developing-custom-grass-tools/* .

Then find `notebook_1_scripts.ipynb` on the left side and double click at it.

### Backup 2: Notebook hosted on Google Colab

Open `colab_notebook.ipynb` in Google Colab.
The disadvantage is that GRASS GIS needs to be compiled first,
so the startup can take several minutes.
All material is presented in a single notebook.

## Abstract

Learn how to develop custom tools (aka addons or modules) for GRASS GIS in Python and, if you like, in C.

Python scripting is powerful, but what is even more powerful is turning a script into a GRASS tool with just a few tricks and tweaks we will cover in this workshop. When you develop a GRASS tool (aka module), you get a graphical user interface (GUI), command line interface, and convenience you and your users will appreciate. Such tools can be published in a community-maintained addon repository which helps not only to distribute the tool, but also to maintain the code in the long term.

We will focus on Python, but we will cover tools written in C, too, because even compiled tools in C and C++ can be in this community-maintained repository and distributed to users.

## Authors

* Vaclav Petras, NC State University, Center for Geospatial Analytics
* Anna Petrasova, NC State University, Center for Geospatial Analytics

## License

This material is dual licensed under GNU FDL 1.3 and CC BY-SA 4.0.
