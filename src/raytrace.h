//
//  raytrace.h
//  C-Ray
//
//  Created by Valtteri Koskivuori on 27/04/2017.
//  Copyright © 2017 Valtteri Koskivuori. All rights reserved.
//

#pragma once

struct scene;

/**
 Ray intersection type enum
 */
enum currentType {
	hitTypePolygon,
	hitTypeSphere,
	hitTypeNone
};


/**
 Shading information, usually computed and stored by a ray intersection function
 */
struct shadeInfo {
	struct vector hitPoint;
	struct vector normal;
	struct material currentMaterial;
	enum currentType type;
	bool hasHit;
	int mtlIndex;
	int objIndex;
	double closestIntersection;
};

struct color rayTrace(struct lightRay *incidentRay, struct scene *worldScene);
