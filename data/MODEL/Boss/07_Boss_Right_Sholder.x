xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 21;
 -82.36628;-22.97983;36.79980;,
 -41.62723;-32.54033;52.09807;,
 -41.62723;32.74417;52.09807;,
 -82.36628;23.18351;36.79980;,
 -41.62723;65.38638;-0.13387;,
 -82.36628;46.26513;-0.13387;,
 -41.62723;32.74417;-52.36598;,
 -82.36628;23.18351;-37.06754;,
 -41.62723;-32.54033;-52.36598;,
 -82.36628;-22.97983;-37.06754;,
 -41.62723;-65.18231;-0.13387;,
 -82.36628;-46.06090;-0.13387;,
 -41.62723;-32.54033;52.09807;,
 -82.36628;-22.97983;36.79980;,
 -0.88811;-22.97983;36.79980;,
 -0.88811;23.18351;36.79980;,
 -0.88811;46.26513;-0.13387;,
 -0.88811;23.18351;-37.06754;,
 -0.88811;-22.97983;-37.06754;,
 -0.88811;-46.06090;-0.13387;,
 -0.88811;-22.97983;36.79980;;
 
 20;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;1,14,15,2;,
 4;2,15,16,4;,
 4;4,16,17,6;,
 4;6,17,18,8;,
 4;8,18,19,10;,
 4;10,19,20,12;,
 3;9,11,7;,
 3;7,11,5;,
 3;5,11,3;,
 3;3,11,13;,
 3;14,19,15;,
 3;15,19,16;,
 3;16,19,17;,
 3;17,19,18;;
 
 MeshMaterialList {
  2;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.062745;0.062745;0.062745;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  20;
  -0.404394;-0.441700;0.800853;,
  -0.404394;0.441698;0.800855;,
  -0.424887;0.905246;0.000000;,
  -0.404396;0.441698;-0.800854;,
  -0.404397;-0.441700;-0.800852;,
  -0.424885;-0.905247;0.000001;,
  -0.000000;-0.482952;0.875647;,
  -0.000000;0.482949;0.875649;,
  -0.000000;1.000000;0.000000;,
  -0.000000;0.482949;-0.875648;,
  -0.000000;-0.482952;-0.875647;,
  -0.000000;-1.000000;0.000001;,
  0.404393;-0.441700;0.800854;,
  0.404393;0.441698;0.800855;,
  0.424886;0.905247;0.000000;,
  0.404395;0.441698;-0.800854;,
  0.404396;-0.441700;-0.800852;,
  0.424885;-0.905247;0.000001;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;;
  20;
  4;0,6,7,1;,
  4;1,7,8,2;,
  4;2,8,9,3;,
  4;3,9,10,4;,
  4;4,10,11,5;,
  4;5,11,6,0;,
  4;6,12,13,7;,
  4;7,13,14,8;,
  4;8,14,15,9;,
  4;9,15,16,10;,
  4;10,16,17,11;,
  4;11,17,12,6;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;;
 }
 MeshTextureCoords {
  21;
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.250000;,
  0.333330;0.500000;,
  0.333330;0.250000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.666670;0.500000;,
  0.666670;0.250000;,
  0.833330;0.500000;,
  0.833330;0.250000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.000000;0.750000;,
  0.166670;0.750000;,
  0.333330;0.750000;,
  0.500000;0.750000;,
  0.666670;0.750000;,
  0.833330;0.750000;,
  1.000000;0.750000;;
 }
}
