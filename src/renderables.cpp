#include "renderables.hpp"

Renderables* Renderables::s_instance = nullptr;   //Initialization of the static pointer

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

    if (!menu_background.loadFromFile("images/menu_background.png")) {
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

    if (!attack.loadFromFile("images/attack-sound.wav")) {
        std::cout << "Error: Audio not found" << std::endl; 
        return;
    }

    if (!select.loadFromFile("images/select-sound.wav")) {
        std::cout << "Error: Audio not found" << std::endl; 
        return;
    }

    attack_sound.setBuffer(attack);
    //attack_sound.setVolume(50);

    select_sound.setBuffer(select);
    //select_sound.setVolume(80);

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
    menu_background_sprite.setTexture(menu_background);
    msc_sprite.setTexture(msc);
    pathTile_sprite.setTexture(pathTile);
    project_sprite.setTexture(project);
    startTile_sprite.setTexture(startTile);
    teekkari_1_sprite.setTexture(teekkari_1);
    teekkari_2_sprite.setTexture(teekkari_2);
    teekkari_3_sprite.setTexture(teekkari_3);
    towerTile_sprite.setTexture(towerTile);
    s_instance = this;
}

sf::Sprite& Renderables::getBachelor1Sprite() {
    return s_instance->bachelor_1_sprite;
}

sf::Sprite& Renderables::getBachelor2Sprite() {
    return s_instance->bachelor_2_sprite;
}

sf::Sprite& Renderables::getBachelor3Sprite() {
    return s_instance->bachelor_3_sprite;
}

sf::Sprite& Renderables::getBachelorsThesisSprite() {
    return s_instance->bachelors_thesis_sprite;
}

sf::Sprite& Renderables::getBackgroundSprite() {
    return s_instance->background_sprite;
}

sf::Sprite& Renderables::getBscSprite() {
    return s_instance->bsc_sprite;
}

sf::Sprite& Renderables::getCalculatorSprite() {
    return s_instance->calculator_sprite;
}

sf::Sprite& Renderables::getCoffeeTableSprite() {
    return s_instance->coffee_table_sprite;
}

sf::Sprite& Renderables::getDoctor1Sprite() {
    return s_instance->doctor_1_sprite;
}

sf::Sprite& Renderables::getDoctor2Sprite() {
    return s_instance->doctor_2_sprite;
}

sf::Sprite& Renderables::getDoctor3Sprite() {
    return s_instance->doctor_3_sprite;
}

sf::Sprite& Renderables::getDoctoralThesisSprite() {
    return s_instance->doctoral_thesis_sprite;
}

sf::Sprite& Renderables::getDscSprite() {
    return s_instance->dsc_sprite;
}

sf::Sprite& Renderables::getEndtileSprite() {
    return s_instance->endTile_sprite;
}

sf::Sprite& Renderables::getEssaySprite() {
    return s_instance->essay_sprite;
}

sf::Sprite& Renderables::getFreshman1Sprite() {
    return s_instance->freshman_1_sprite;
}

sf::Sprite& Renderables::getFreshman2Sprite() {
    return s_instance->freshman_2_sprite;
}

sf::Sprite& Renderables::getFreshman3Sprite() {
    return s_instance->freshman_3_sprite;
}

sf::Sprite& Renderables::getHomeworkSprite() {
    return s_instance->homework_sprite;
}

sf::Sprite& Renderables::getMaster1Sprite() {
    return s_instance->master_1_sprite;
}

sf::Sprite& Renderables::getMaster2Sprite() {
    return s_instance->master_2_sprite;
}

sf::Sprite& Renderables::getMaster3Sprite() {
    return s_instance->master_3_sprite;
}

sf::Sprite& Renderables::getMastersThesisSprite() {
    return s_instance->masters_thesis_sprite;
}

sf::Sprite& Renderables::getMenuBackgroundSprite() {
    return s_instance->menu_background_sprite;
}

sf::Sprite& Renderables::getMscSprite() {
    return s_instance->msc_sprite;
}

sf::Sprite& Renderables::getPathtileSprite() {
    return s_instance->pathTile_sprite;
}

sf::Sprite& Renderables::getProjectSprite() {
    return s_instance->project_sprite;
}

sf::Sprite& Renderables::getStarttileSprite() {
    return s_instance->startTile_sprite;
}

sf::Sprite& Renderables::getTeekkari1Sprite() {
    return s_instance->teekkari_1_sprite;
}

sf::Sprite& Renderables::getTeekkari2Sprite() {
    return s_instance->teekkari_2_sprite;
}

sf::Sprite& Renderables::getTeekkari3Sprite() {
    return s_instance->teekkari_3_sprite;
}

sf::Sprite& Renderables::getTowertileSprite() {
    return s_instance->towerTile_sprite;
}

sf::Sound& Renderables::getAttackSound() {
    return s_instance->attack_sound;
}

sf::Sound& Renderables::getSelectSound() {
    return s_instance->select_sound;
}
