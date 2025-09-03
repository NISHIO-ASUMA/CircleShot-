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
 47.58593;-31.59248;46.49880;,
 266.69790;-37.49341;63.86559;,
 267.60684;11.52697;70.41078;,
 46.23364;26.72778;48.42042;,
 266.37920;64.09221;11.93277;,
 45.66643;57.84167;3.37553;,
 272.13243;27.29652;-48.36049;,
 46.45181;30.63564;-43.59100;,
 271.66582;-33.51378;-54.46670;,
 47.80446;-27.68453;-45.51259;,
 267.59424;-67.67067;6.66537;,
 48.37118;-58.79854;-0.46766;,
 266.69790;-37.49341;63.86559;,
 47.58593;-31.59248;46.49880;,
 302.91446;-17.33962;12.89119;,
 -0.36785;1.40817;-0.24646;,
 -0.36785;1.40817;-0.24646;,
 -0.36785;1.40817;-0.24646;,
 -0.36785;1.40817;-0.24646;,
 -0.36785;1.40817;-0.24646;,
 -0.36785;1.40817;-0.24646;;
 
 18;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 3;1,14,2;,
 3;2,14,4;,
 3;4,14,6;,
 3;6,14,8;,
 3;8,14,10;,
 3;10,14,12;,
 3;3,15,0;,
 3;5,16,3;,
 3;7,17,5;,
 3;9,18,7;,
 3;11,19,9;,
 3;13,20,11;;
 
 MeshMaterialList {
  2;
  18;
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
   0.645333;0.138039;0.020706;1.000000;;
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
  24;
  -0.472248;-0.472049;0.744414;,
  -0.463321;0.364968;0.807547;,
  -0.579534;0.772337;0.260071;,
  -0.426282;0.460276;-0.778736;,
  -0.548079;-0.193456;-0.813747;,
  -0.574598;-0.785842;-0.228667;,
  0.251474;-0.628786;0.735792;,
  -0.069234;0.398011;0.914764;,
  -0.030397;0.784251;0.619698;,
  -0.017309;0.523018;-0.852146;,
  -0.028918;0.066326;-0.997379;,
  0.607752;-0.772843;-0.182622;,
  0.994778;-0.072512;0.071830;,
  -0.833888;-0.026827;0.551282;,
  -0.001722;0.859523;-0.511095;,
  -0.028569;-0.847877;-0.529423;,
  0.440720;-0.783163;-0.438659;,
  -0.055961;-0.874063;0.482578;,
  0.828262;-0.089220;0.553193;,
  0.874770;0.155605;0.458874;,
  0.908373;0.408598;0.088914;,
  0.926491;0.225153;-0.301532;,
  0.903218;0.036013;-0.427668;,
  -0.817989;0.012838;-0.575091;;
  18;
  4;0,6,7,1;,
  4;1,7,8,2;,
  4;14,14,9,3;,
  4;3,9,10,4;,
  4;15,16,11,5;,
  4;17,17,6,0;,
  3;18,12,19;,
  3;19,12,20;,
  3;20,12,21;,
  3;21,12,22;,
  3;16,12,11;,
  3;11,12,6;,
  3;1,13,0;,
  3;2,13,1;,
  3;3,23,2;,
  3;4,23,3;,
  3;5,23,4;,
  3;0,13,5;;
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
  0.500000;0.865380;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;;
 }
}
