/////////////////////////////////////////////////////////////////////////////
//  HRIR                                                                   //
//  Copyright (C) 2016  Ciarán Connor                                      //
//                                                                         //
//  This program is free software: you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by   //
//  the Free Software Foundation, either version 3 of the License, or      //
//  (at your option) any later version.                                    //
//                                                                         //
//  This program is distributed in the hope that it will be useful,        //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//  GNU General Public License for more details.                           //
//                                                                         //
//  You should have received a copy of the GNU General Public License      //
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
/////////////////////////////////////////////////////////////////////////////

#ifndef HRIR_H_INCLUDED
#define HRIR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class HRIR
{
public:
    HRIR();

    void update (double, double);

    AudioSampleBuffer leftEar;
    AudioSampleBuffer rightEar;

private:
    unsigned int sampleRate;
    unsigned int diffused;
};

#endif  // HRIR_H_INCLUDED
