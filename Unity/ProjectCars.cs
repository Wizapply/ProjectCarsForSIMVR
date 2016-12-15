using UnityEngine;
using System.Collections;
using System;

public class ProjectCars : MonoBehaviour {

    [Serializable]
    public class Buildinfo
    {
        public int mBuildVersionNumber;
        public int mVersion;
    }

    [Serializable]
    public class CarDamage
    {
        public int mAeroDamage;
        public int mCrashState;
        public double mEngineDamage;
    }

    [Serializable]
    public class CarState
    {
        public bool mAntiLockActive;
        public bool mBoostActive;
        public int mBoostAmount;
        public int mBrake;
        public int mCarFlags;
        public int mClutch;
        public int mFuelCapacity;
        public double mFuelLevel;
        public double mFuelPressureKPa;
        public int mGear;
        public int mLastOpponentCollisionIndex;
        public int mLastOpponentCollisionMagnitude;
        public int mMaxRPM;
        public int mNumGears;
        public double mOdometerKM;
        public double mOilTempCelsius;
        public double mRpm;
        public double mSpeed;
        public double mSteering;
        public double mThrottle;
        public double mWaterPressureKPa;
        public double mWaterTempCelsius;
    }

    [Serializable]
    public class EventInformation
    {
        public int mLapsInEvent;
        public double mTrackLength;
        public string mTrackLocation;
        public string mTrackVariation;
    }

    [Serializable]
    public class Flags
    {
        public int mHighestFlagColour;
        public int mHighestFlagReason;
    }

    [Serializable]
    public class GameStates
    {
        public int mGameState;
        public int mRaceState;
        public int mSessionState;
    }

    [Serializable]
    public class MotionAndDeviceRelated
    {
        public double[] mAngularVelocity;
        public double[] mExtentsCentre;
        public double[] mLocalAcceleration;
        public double[] mLocalVelocity;
        public double[] mOrientation;
        public double[] mWorldAcceleration;
        public double[] mWorldVelocity;
    }

    [Serializable]
    public class MParticipantInfo
    {
        public int mCurrentLap;
        public int mCurrentLapDistance;
        public int mCurrentSector;
        public bool mIsActive;
        public int mLapsCompleted;
        public string mName;
        public int mRacePosition;
        public double[] mWorldPosition;
    }

    [Serializable]
    public class Participants
    {
        public int mNumParticipants;
        public MParticipantInfo[] mParticipantInfo;
        public int mViewedParticipantIndex;
    }

    [Serializable]
    public class PitInfo
    {
        public int mPitMode;
        public int mPitSchedule;
    }

    [Serializable]
    public class Timings
    {
        public int mBestLapTime;
        public int mCurrentSector1Time;
        public int mCurrentSector2Time;
        public int mCurrentSector3Time;
        public int mCurrentTime;
        public int mEventTimeRemaining;
        public int mFastestSector1Time;
        public int mFastestSector2Time;
        public int mFastestSector3Time;
        public bool mLapInvalidated;
        public int mLastLapTime;
        public int mPersonalFastestLapTime;
        public int mPersonalFastestSector1Time;
        public int mPersonalFastestSector2Time;
        public int mPersonalFastestSector3Time;
        public int mSplitTime;
        public int mSplitTimeAhead;
        public int mSplitTimeBehind;
        public double mWorldFastestLapTime;
        public double mWorldFastestSector1Time;
        public double mWorldFastestSector2Time;
        public double mWorldFastestSector3Time;
    }

    [Serializable]
    public class UnfilteredInput
    {
        public int mUnfilteredBrake;
        public int mUnfilteredClutch;
        public double mUnfilteredSteering;
        public double mUnfilteredThrottle;
    }

    [Serializable]
    public class VehicleInformation
    {
        public string mCarClassName;
        public string mCarName;
    }

    [Serializable]
    public class Weather
    {
        public double mAmbientTemperature;
        public double mCloudBrightness;
        public int mRainDensity;
        public double mTrackTemperature;
        public double mWindDirectionX;
        public double mWindDirectionY;
        public double mWindSpeed;
    }

    [Serializable]
    public class WheelsAndTyres
    {
        public int[] mBrakeDamage;
        public double[] mBrakeTempCelsius;
        public int[] mSuspensionDamage;
        public int[] mTerrain;
        public double[] mTyreCarcassTemp;
        public int[] mTyreFlags;
        public int[] mTyreGrip;
        public double[] mTyreHeightAboveGround;
        public double[] mTyreInternalAirTemp;
        public int[] mTyreLateralStiffness;
        public double[] mTyreLayerTemp;
        public double[] mTyreRPS;
        public double[] mTyreRimTemp;
        public double[] mTyreSlipSpeed;
        public double[] mTyreTemp;
        public double[] mTyreTreadTemp;
        public double[] mTyreWear;
        public double[] mTyreY;
    }

    [Serializable]
    public class RootObject
    {
        public Buildinfo buildinfo;
        public CarDamage carDamage;
        public CarState carState;
        public EventInformation eventInformation;
        public Flags flags;
        public GameStates gameStates;
        public MotionAndDeviceRelated motionAndDeviceRelated;
        public Participants participants;
        public PitInfo pitInfo;
        public Timings timings;
        public UnfilteredInput unfilteredInput;
        public VehicleInformation vehicleInformation;
        public Weather weather;
        public WheelsAndTyres wheelsAndTyres;
    }

    public RootObject rootObject;

	void Start () {
        StartCoroutine("GetJson");
	}

    IEnumerator GetJson()
    {
        var www = new WWW("http://localhost:8080/crest/v1/api");
        yield return www;

        if(!string.IsNullOrEmpty(www.error))
        {
            Debug.Log("APIを取得できませんでした");
            yield break;
        }

        var json = www.text;
        rootObject = JsonUtility.FromJson<RootObject>(json);
    }
	
	// Update is called once per frame
	void Update () {
        StartCoroutine("GetJson");
	}
}
