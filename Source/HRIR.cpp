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

#include "../JuceLibraryCode/JuceHeader.h"
#include "mit-hrtf-lib/mit_hrtf_lib.h"
#include "HRIR.h"

HRIR::HRIR()
:   sampleRate (44100),
    diffused (0)
{
    // Member variables set in initializer list.
}

void HRIR::update (double azimuth, double elevation)
{
    int nAzimuth = (int) azimuth;
    int nElevation = (int) elevation;
    int taps = mit_hrtf_availability (nAzimuth, nElevation, sampleRate, diffused);

    if (taps)
    {
        leftEar.setSize (1, taps);
        rightEar.setSize (1, taps);

        AudioBuffer<short> leftShort (1, taps);
        AudioBuffer<short> rightShort (1, taps);

        short* const writeLeft = leftShort.getWritePointer (0);
        short* const writeRight = rightShort.getWritePointer (0);

        taps = mit_hrtf_get (&nAzimuth, &nElevation, sampleRate, diffused, writeLeft, writeRight);

        float* const leftEarWrite = leftEar.getWritePointer (0);
        float* const rightEarWrite = rightEar.getWritePointer (0);

        const short* const readLeft = leftShort.getReadPointer (0);
        const short* const readRight = rightShort.getReadPointer (0);

        for (int n = 0; n < taps; ++n)
        {
            leftEarWrite[n] = readLeft[n] / 32768.0f;
            rightEarWrite[n] = readRight[n] / 32768.0f;
        }
    }
}
