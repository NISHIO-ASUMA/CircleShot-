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
 -136.64561;-10.20883;11.96944;,
 -21.17492;-11.02154;25.33418;,
 -19.92676;15.03173;28.84408;,
 -136.32942;20.77690;13.04908;,
 -18.42740;43.12451;-1.46928;,
 -135.14675;37.43558;-10.31070;,
 -14.83773;23.79012;-32.75277;,
 -134.27910;23.10884;-34.75014;,
 -16.07715;-8.52832;-36.04763;,
 -134.59509;-7.87669;-35.82986;,
 -20.09617;-26.89899;-4.42640;,
 -135.77818;-24.53571;-12.46999;,
 -21.17492;-11.02154;25.33418;,
 -136.64561;-10.20883;11.96944;,
 -0.61088;0.22493;-0.39663;,
 -160.46536;6.94467;-13.21143;,
 -160.46536;6.94467;-13.21143;,
 -160.46536;6.94467;-13.21143;,
 -160.46536;6.94467;-13.21143;,
 -160.46536;6.94467;-13.21143;,
 -160.46536;6.94467;-13.21143;;
 
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
  -0.496232;-0.461328;0.735480;,
  -0.490812;0.369908;0.788842;,
  -0.588242;0.771456;0.242544;,
  -0.396247;0.466765;-0.790645;,
  -0.513617;-0.176180;-0.839737;,
  -0.568354;-0.780227;-0.261189;,
  0.228116;-0.629017;0.743169;,
  -0.111293;0.392804;0.912863;,
  -0.069620;0.775202;0.627865;,
  0.004124;0.521387;-0.853311;,
  0.007212;0.067861;-0.997669;,
  0.611471;-0.773840;-0.165151;,
  0.989016;-0.098529;0.110178;,
  -0.850959;-0.009770;0.525140;,
  0.000102;0.856800;-0.515648;,
  0.009005;-0.840398;-0.541895;,
  0.458823;-0.779969;-0.425594;,
  -0.056524;-0.872133;0.485992;,
  0.800183;-0.117567;0.588120;,
  0.856019;0.127238;0.501040;,
  0.914594;0.383076;0.129501;,
  0.942254;0.196873;-0.270921;,
  0.916881;0.005528;-0.399122;,
  -0.790397;0.032086;-0.611755;;
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
