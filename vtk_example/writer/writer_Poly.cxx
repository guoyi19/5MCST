//refer to https://lorensen.github.io/VTKExamples/site/Cxx/Filtering/Delaunay2D/
//refer to https://vtk.org/Wiki/VTK/Examples/Boneyard/Cxx/Modelling/Delaunay3DAlpha


#include <vtkPolyDataReader.h>
#include <vtkUnstructuredGridWriter.h>

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkDelaunay3D.h>
#include <vtkXMLDataSetWriter.h>

int main(int argc, char *argv[])
{
    // Parse command line arguments
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " Filename" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];

    // Read all the data from the file
    vtkSmartPointer<vtkPolyDataReader> reader =
        vtkSmartPointer<vtkPolyDataReader>::New();
    reader->SetFileName(filename.c_str());
    reader->Update();

    // get the specific polydata and check the results
    vtkPolyData *polydata = reader->GetOutput();

    // Triangulate the grid points
    vtkSmartPointer<vtkDelaunay3D> delaunay =
        vtkSmartPointer<vtkDelaunay3D>::New();
    delaunay->SetInputData(polydata);
    delaunay->Update();


    // Write the file by vtkXMLDataSetWriter
    vtkSmartPointer<vtkXMLDataSetWriter> writer =
        vtkSmartPointer<vtkXMLDataSetWriter>::New();
    writer->SetFileName("./delaunay_3dbox.xml");

    // get the specific polydata and check the results
    writer->SetInputConnection(delaunay->GetOutputPort());
    // writer->SetInputData(delaunay->GetOutputPort());
    // Optional - set the mode. The default is binary.
    writer->SetDataModeToBinary();
    // writer->SetDataModeToAscii();
    writer->Write();




    // write the file by 
    // Write the file by vtkXMLDataSetWriter
    vtkSmartPointer<vtkUnstructuredGridWriter> polywriter =
        vtkSmartPointer<vtkUnstructuredGridWriter>::New();
    polywriter->SetFileName("./delaunay_3dbox_unstructure.vtk");

    // get the specific polydata and check the results
    // writer->SetInputData???
    polywriter->SetInputConnection(delaunay->GetOutputPort());
    //polywriter->SetInputData(delaunay->GetOutputPort());

    // Optional - set the mode. The default is binary.
    writer->SetDataModeToBinary();
    //polywriter->SetDataModeToAscii();
    polywriter->Write();


    std::cout << "ok to write by polywriter"<< std::endl;
    return 0;
}