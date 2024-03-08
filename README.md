<!-- TABLE OF CONTENTS -->
Table of Content
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
  </ol>

<!-- ABOUT THE PROJECT -->
## About The Project

This is a collection of software abstractions cannot be categorize as drivers (CoreDrivers, PeripheralDrivers) such as Hashing Operations, Fie System managers, System time (NTP servers). 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.


### Installation

1. Clone the repo to the component directory of the esp-idf project
   ```sh
   git clone --recursive https://github.com/Omegaki113r/PreBuilt-OmegaESP32Services.git
   ```
2. Including pre built libraries in the CMakeLists.txt file
   ```cmake
    set(HEADERS components/PreBuilt-OmegaESP32Services/OmegaXXXXXXController)
    set(PRE-COMPILED_LIBS libOmegaHashController.a)
    add_prebuilt_library(
        OMEGALIBS ${PRE-COMPILED_LIBS} 
        PRIV_REQUIRES XXXXXXXX
        )
    target_link_libraries(
        ${COMPONENT_LIB} PRIVATE OMEGALIBS
        )
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

[pdf version of the documentation](https://github.com/Omegaki113r/PreBuilt-OmegaESP32Services/blob/main/Docs/CodeDocs/reference_manual.pdf)

[online version documentation](https://omegaesp32servicesdocs.web.app/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [x] Add OmegaHashController
- [x] Add OmegaFileSystemController


See the [open issues](https://github.com/Omegaki113r/PreBuilt-OmegaESP32Services/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>
