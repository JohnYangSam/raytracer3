#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "Scene.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "Triangle.h"

#define BOUNCE_DEPTH_DEFAULT    5
#define SHADOW_BIAS_DEFAULT     0

using namespace std;


Scene::Scene(std::string sceneFilename) :
    /* Initialize empty states */
    /* mCamera later */
    /* mImagePlane later */
    /* Use an initialization list to initialize objects that can
     * be of a variable size when made, but will be set to that
     * size once they are created so that the entire class knows
     * how big it needs to be. We use pointers to the vectors in
     * this case, but if we wanted to initialize them to fixed
     * sizes with constants, this is where we would do it
     */
    mPointLights(       new vector<PointLight>()),
    mDirectionalLights( new vector<DirectionalLight>()),
    mAmbientLights(     new vector<AmbientLight>()),
    mSceneObjects(      new vector<SceneObject>()),
    mMatrixStack(       new stack<STTransform4>()),
    mCurrMaterial(      new Material(STColor3f(0.0f,0.0f,0.0f),
                                 STColor3f(0.0f,0.0f,0.0f),
                                 STColor3f(0.0f,0.0f,0.0f),
                                 STColor3f(0.0f,0.0f,0.0f),
                                 0)),
    mShadowBias(    SHADOW_BIAS_DEFAULT),
    mBounceDepth(   BOUNCE_DEPTH_DEFAULT)
    /* mOutputFilename later has to be a pointer since it is dynamic */

{
    /** Initialization setup */
    
    //Initialze matrix stack with the identity matrix
    mMatrixStack->push(STTransform4::Identity());
    
	Parse(sceneFilename);
}

void Scene::Parse(std::string sceneFilename)
{
	BeganParsing();

	std::ifstream sceneFile(sceneFilename.c_str());

	// Die if we couldn't find the file
	if (sceneFile.fail())
	{
		printf("Scene::Parse - Could not find input scene file '%s'\n", sceneFilename.c_str());
		exit(1);
	}

	char line[1024];
	while (!sceneFile.eof())
	{
		sceneFile.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;

		if (command == "Camera")
		{
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, f, a;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> lz >> f >> a;
			STPoint3 eye(ex, ey, ez);
			STVector3 up(ux, uy, uz);
			STPoint3 lookAt(lx, ly, lz);
			ParsedCamera(eye, up, lookAt, f, a);
		}
		else
		if (command == "Output")
		{
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			ParsedOutput(w, h, fname);
		}
		else
		if (command == "BounceDepth")
		{
			int depth;
			ss >> depth;
			ParsedBounceDepth(depth);
		}
		else if (command == "ShadowBias")
		{
			float bias;
			ss >> bias;
			ParsedShadowBias(bias);
		}
		else
		if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else
		if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else
		if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else
		if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else
		if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
		else
		if (command == "Sphere")
		{
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			STPoint3 center(cx, cy, cz);
			ParsedSphere(center, r);
		}
		else
		if (command == "Triangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			STPoint3 v[3];
			v[0] = STPoint3(x1, y1, z1);
			v[1] = STPoint3(x2, y2, z2);
			v[2] = STPoint3(x3, y3, z3);
			ParsedTriangle(v[0], v[1], v[2]);
		}
		else
		if (command == "AmbientLight")
		{
			float r, g, b;
			ss >> r >> g >> b;
			STColor3f col(r, g, b);
			ParsedAmbientLight(col);
		}
		else
		if (command == "PointLight")
		{
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			STPoint3 pos(px, py, pz);
			STColor3f col(r, g, b);
			ParsedPointLight(pos, col);
		}
		else
		if (command == "DirectionalLight")
		{
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			STVector3 dir(dx, dy, dz);
			STColor3f col(r, g, b);
			ParsedDirectionalLight(dir, col);
		}
		else
		if (command == "Material")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> shine;
			STColor3f amb(ra, ga, ba);
			STColor3f diff(rd, gd, bd);
			STColor3f spec(rs, gs, bs);
			STColor3f mirr(rr, gr, br);
			ParsedMaterial(amb, diff, spec, mirr, shine);
		}
	}
	sceneFile.close();

	FinishedParsing();
}

//Called at the very beginning of parsing
void Scene::BeganParsing()
{
    cout << "Starting parsing." << endl;
}

//Called at the very end of parsing
void Scene::FinishedParsing()
{
    cout << "Finished parsing scene file." << endl;
}

void Scene::ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect)
{
    mCamera = new Camera(eye, up, lookAt, fovy, aspect);
}

void Scene::ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename)
{
    mImagePlane = new ImagePlane(*mCamera, imgWidth, imgHeight);
    mOutputFileName = new std::string(outputFilename);
}

void Scene::ParsedBounceDepth(int depth)
{
    mBounceDepth = depth;
}

void Scene::ParsedShadowBias(float bias)
{
    mShadowBias = bias;
}

void Scene::ParsedPushMatrix()
{
    //Make a copy of the current matrix and push it on the stack
    STTransform4 transformCopy = STTransform4(mMatrixStack->top());
    mMatrixStack->push(transformCopy);
}

void Scene::ParsedPopMatrix()
{
    mMatrixStack->pop();
}

void Scene::ParsedRotate(float rx, float ry, float rz)
{
    mMatrixStack->push(STTransform4::Rotation(rx, ry, rz));
}

void Scene::ParsedScale(float sx, float sy, float sz)
{
    mMatrixStack->push(STTransform4::Scaling(sx, sy, sz));
}

void Scene::ParsedTranslate(float tx, float ty, float tz)
{
    mMatrixStack->push(STTransform4::Translation(tx, ty, tz));
}

void Scene::ParsedSphere(const STPoint3& center, float radius)
{
    Shape* sphere = new Sphere(center, radius);
    STTransform4 currTransform = mMatrixStack->top();
    mSceneObjects->push_back(SceneObject(sphere, mCurrMaterial, currTransform));
}

void Scene::ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3)
{
    Shape* triangle = new Triangle(v1, v2, v3);
    STTransform4 currTransform = mMatrixStack->top();
    mSceneObjects->push_back(SceneObject(triangle, mCurrMaterial, currTransform));
}

void Scene::ParsedAmbientLight(const STColor3f& col)
{
    mAmbientLights->push_back(AmbientLight(col));
}

void Scene::ParsedPointLight(const STPoint3& loc, const STColor3f& col)
{
    mPointLights->push_back(PointLight(col, loc));
}

void Scene::ParsedDirectionalLight(const STVector3& dir, const STColor3f& col)
{
    mDirectionalLights->push_back(DirectionalLight(col, dir));
}

void Scene::ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine)
{
    mCurrMaterial = Material(amb, diff, spec, mirr, shine);
    
}

STImage render() {
    mImagePlane.
    STImage image = new STImage(<#int width#>, <#int height#>)
    
}