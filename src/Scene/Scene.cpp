#include <vector>
#include <iostream>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "../Tools/FileReader.h"
#include "../Graphics/RenderComponent.h"
#include "SceneObject.h"
#include "Scene.h"

Scene::Scene(const std::string &p_filePath) {
    Assimp::Importer importer;
    const aiScene* scene = FileReader::ReadScene(p_filePath, importer);
    ConvertNodesToObjects(scene->mRootNode, *scene);
}

const std::vector<SceneObjectPtr> Scene::GetSceneObjects() const {
    return m_sceneObjects;
}

Scene::~Scene() {
    m_sceneObjects.clear();
}

void Scene::ConvertNodesToObjects(const aiNode *p_node, const aiScene &p_scene) {
    if (p_node->mNumMeshes > 0) {
        SceneObjectPtr object = SceneObjectPtr(new SceneObject(p_node, p_scene));
        m_sceneObjects.push_back(object);
    }
    for (unsigned int c = 0; c < p_node->mNumChildren; ++c) {
        ConvertNodesToObjects(p_node->mChildren[c], p_scene);
    }

    if (p_scene.mNumCameras > 0) {
        aiCamera *aiCamera = p_scene.mCameras[0];
        m_camera.m_farDistance = aiCamera->mClipPlaneFar;
        m_camera.m_nearDistance = aiCamera->mClipPlaneNear;
        m_camera.m_viewAngle = aiCamera->mHorizontalFOV;
        m_camera.m_viewRatio = 4.0f / 3.0f;
        m_camera.m_lookAtVec = glm::vec3(aiCamera->mLookAt.x, aiCamera->mLookAt.y, aiCamera->mLookAt.z);
        m_camera.m_position = glm::vec3(aiCamera->mPosition.x, aiCamera->mPosition.y, aiCamera->mPosition.z);
        m_camera.m_up = glm::vec3(aiCamera->mUp.x, aiCamera->mUp.y, aiCamera->mUp.z);
    }
    if(p_scene.mNumLights > 0){
        aiLight *aiLight = p_scene.mLights[0];
        //z axis is the other way around in opengl compared to blender
        m_light.m_position = glm::vec3(aiLight->mPosition.x,aiLight->mPosition.y, -aiLight->mPosition.z);
        m_light.m_intensity = aiLight->mAttenuationLinear;
    }


}

const Camera Scene::GetCamera() const {
    return m_camera;
}
