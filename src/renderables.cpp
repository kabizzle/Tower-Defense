#include "renderables.hpp"

Renderables::Renderables() {
    if (!bachelor_1.loadFromFile("images/bachelor.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!background.loadFromFile("images/background.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!bachelor_2.loadFromFile("images/bachelor_upgraded.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!bachelor_3.loadFromFile("images/bachelor_upgraded_twice.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!bachelors_thesis.loadFromFile("images/bachelors_thesis.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!bsc.loadFromFile("images/bsc.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!calculator.loadFromFile("images/calculator.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!coffee_table.loadFromFile("images/coffee_table.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!doctor_1.loadFromFile("images/doctor.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!doctor_2.loadFromFile("images/doctor_upgraded.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!doctor_3.loadFromFile("images/doctor_upgraded_twice.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!doctoral_thesis.loadFromFile("images/doctoral_thesis.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!dsc.loadFromFile("images/dsc.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!endTile.loadFromFile("images/endTile.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!essay.loadFromFile("images/essay.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!freshman_1.loadFromFile("images/freshman.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!freshman_2.loadFromFile("images/freshman_upgraded.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!freshman_3.loadFromFile("images/freshman_upgraded_twice.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!homework.loadFromFile("images/homework.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!master_1.loadFromFile("images/master.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!master_2.loadFromFile("images/master_upgraded.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!master_3.loadFromFile("images/master_upgraded_twice.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!masters_thesis.loadFromFile("images/masters_thesis.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!msc.loadFromFile("images/msc.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!pathTile.loadFromFile("images/pathTile.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!project.loadFromFile("images/project.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!startTile.loadFromFile("images/startTile.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!teekkari_1.loadFromFile("images/teekkari.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!teekkari_2.loadFromFile("images/teekkari_upgraded.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!teekkari_3.loadFromFile("images/teekkari_upgraded_twice.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    if (!towerTile.loadFromFile("images/towerTile.png")) {
        std::cout << "Error: Image not found" << std::endl; 
        return;
    }

    bachelor_1_sprite.setTexture(bachelor_1);
    bachelor_2_sprite.setTexture(bachelor_2);
    bachelor_3_sprite.setTexture(bachelor_3);
    bachelors_thesis_sprite.setTexture(bachelors_thesis);
    background_sprite.setTexture(background);
    bsc_sprite.setTexture(bsc);
    calculator_sprite.setTexture(calculator);
    coffee_table_sprite.setTexture(coffee_table);
    doctor_1_sprite.setTexture(doctor_1);
    doctor_2_sprite.setTexture(doctor_2);
    doctor_3_sprite.setTexture(doctor_3);
    doctoral_thesis_sprite.setTexture(doctoral_thesis);
    dsc_sprite.setTexture(dsc);
    endTile_sprite.setTexture(endTile);
    essay_sprite.setTexture(essay);
    freshman_1_sprite.setTexture(freshman_1);
    freshman_2_sprite.setTexture(freshman_2);
    freshman_3_sprite.setTexture(freshman_3);
    homework_sprite.setTexture(homework);
    master_1_sprite.setTexture(master_1);
    master_2_sprite.setTexture(master_2);
    master_3_sprite.setTexture(master_3);
    masters_thesis_sprite.setTexture(masters_thesis);
    msc_sprite.setTexture(msc);
    pathTile_sprite.setTexture(pathTile);
    project_sprite.setTexture(project);
    startTile_sprite.setTexture(startTile);
    teekkari_1_sprite.setTexture(teekkari_1);
    teekkari_2_sprite.setTexture(teekkari_2);
    teekkari_3_sprite.setTexture(teekkari_3);
    towerTile_sprite.setTexture(towerTile);
    
}

sf::Sprite& Renderables::getBachelor1Sprite() {
    return bachelor_1_sprite;
}

sf::Sprite& Renderables::getBachelor2Sprite() {
    return bachelor_2_sprite;
}

sf::Sprite& Renderables::getBachelor3Sprite() {
    return bachelor_3_sprite;
}

sf::Sprite& Renderables::getBachelorsThesisSprite() {
    return bachelors_thesis_sprite;
}

sf::Sprite& Renderables::getBackgroundSprite() {
    return background_sprite;
}

sf::Sprite& Renderables::getBscSprite() {
    return bsc_sprite;
}

sf::Sprite& Renderables::getCalculatorSprite() {
    return calculator_sprite;
}

sf::Sprite& Renderables::getCoffeeTableSprite() {
    return coffee_table_sprite;
}

sf::Sprite& Renderables::getDoctor1Sprite() {
    return doctor_1_sprite;
}

sf::Sprite& Renderables::getDoctor2Sprite() {
    return doctor_2_sprite;
}

sf::Sprite& Renderables::getDoctor3Sprite() {
    return doctor_3_sprite;
}

sf::Sprite& Renderables::getDoctoralThesisSprite() {
    return doctoral_thesis_sprite;
}

sf::Sprite& Renderables::getDscSprite() {
    return dsc_sprite;
}

sf::Sprite& Renderables::getEndtileSprite() {
    return endTile_sprite;
}

sf::Sprite& Renderables::getEssaySprite() {
    return essay_sprite;
}

sf::Sprite& Renderables::getFreshman1Sprite() {
    return freshman_1_sprite;
}

sf::Sprite& Renderables::getFreshman2Sprite() {
    return freshman_2_sprite;
}

sf::Sprite& Renderables::getFreshman3Sprite() {
    return freshman_3_sprite;
}

sf::Sprite& Renderables::getHomeworkSprite() {
    return homework_sprite;
}

sf::Sprite& Renderables::getMaster1Sprite() {
    return master_1_sprite;
}

sf::Sprite& Renderables::getMaster2Sprite() {
    return master_2_sprite;
}

sf::Sprite& Renderables::getMaster3Sprite() {
    return master_3_sprite;
}

sf::Sprite& Renderables::getMastersThesisSprite() {
    return masters_thesis_sprite;
}

sf::Sprite& Renderables::getMscSprite() {
    return msc_sprite;
}

sf::Sprite& Renderables::getPathtileSprite() {
    return pathTile_sprite;
}

sf::Sprite& Renderables::getProjectSprite() {
    return project_sprite;
}

sf::Sprite& Renderables::getStarttileSprite() {
    return startTile_sprite;
}

sf::Sprite& Renderables::getTeekkari1Sprite() {
    return teekkari_1_sprite;
}

sf::Sprite& Renderables::getTeekkari2Sprite() {
    return teekkari_2_sprite;
}

sf::Sprite& Renderables::getTeekari3Sprite() {
    return teekkari_3_sprite;
}

sf::Sprite& Renderables::getTowertileSprite() {
    return towerTile_sprite;
}