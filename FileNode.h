//
// Created by Adam G.
//

#ifndef CS008_SFML_FINALPROJECT_FILENODE_H
#define CS008_SFML_FINALPROJECT_FILENODE_H

#include <SFML/Graphics.hpp>
#include "GUIComponentAdapter.h"
#include "FileItem.h"

class FileNode : public GUIComponentAdapter {
private:
    FileItem data;

    std::vector<FileNode*> children;

    void toggleChildren();

    void reposition();
};


#endif //CS008_SFML_FINALPROJECT_FILENODE_H
