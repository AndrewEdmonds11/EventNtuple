//
// structs used to record per-track information in TTrees.
// All momenta are in units of MeV/c, time in nsec WRT when the proton bunch pulse peak hits the production target,
// positions are in mm WRT the center of the tracker.
// Dave Brown (LBNL)
//
#ifndef TrkInfo_HH
#define TrkInfo_HH
#include "Offline/DataProducts/inc/GenVector.hh"
#include "Offline/KinKalGeom/inc/SurfaceId.hh"
#include "Offline/MCDataProducts/inc/MCRelationship.hh"
#include "Rtypes.h"
namespace mu2e
{
  // generic information about the track fit at a particular place/time
  struct TrkFitInfo {
    XYZVectorF mom;
    XYZVectorF pos;
    double time;
    float momerr = -1000;  // projected error on the scalar momentum
    bool inbounds = false; // was the intersection within the (literal) surface bounds
    bool gap = false; // was the intersection in a piecewise trajectory gap
    bool early = false; // is this the earliest intersection for this track
    bool late = false; // is this the latest intersection for this track
    int sid = SurfaceIdEnum::unknown; // SurfaceId of the intersected surface, see Offline/KinKalGeom/inc/SurfaceId.hh
    int sindex = 0; // index to the intersected surface (for multi-surface elements like StoppingTarget)
    void reset() { *this = TrkFitInfo(); }
  };
  // structs for specific fit types
  struct CentralHelixInfo {
    // central helix parameters
    float d0=0,phi0=0,omega=0,z0=0,tanDip=0,t0=0;
    float d0err=0,phi0err=0,omegaerr=0,z0err=0,tanDiperr=0,t0err=0;
    // max radius (assuming geometric extrapolation).  This member is deprecated
    // in favor of explicit extrapolation to the OPA
    float maxr = 0;
    void reset() { *this = CentralHelixInfo(); }
  };

  struct LoopHelixInfo {
    // max radius (assuming geometric extrapolation).  This member is deprecated
    // in favor of explicit extrapolation to the OPA
    float maxr = 0;
    // loop helix parameters
    float rad=0,lam=0,cx=0,cy=0,phi0=0,t0=0;
    float raderr=0,lamerr=0,cxerr=0,cyerr=0,phi0err=0,t0err=0;
    void reset() { *this = LoopHelixInfo(); }
  };

  struct KinematicLineInfo {
    float  d0=0, phi0=0, z0=0, theta=0, mom=0,t0=0;
    float  d0err=0, phi0err=0, z0err=0, thetaerr=0, momerr=0,t0err=0;
    void reset() { *this = KinematicLineInfo(); }
  };

  // general information about a track
  struct TrkInfo {
    int status =-1; // Kalman fit status
    int goodfit = 0; // fit is geometrically consistent
    int seedalg = -1; // pat. rec. algorithm
    int fitalg = -1; // final fit algorithm
    int pdg =0;   // PDG code of particle assumed in fit
    int nhits =0;     // # hits associated to this track
    int ndof =0;      // number of degrees of freedom in the fit
    int nactive =0;   // number of active hits (actually used in the fit)
    int ndouble =0,ndactive =0; // number of double-hit panels, and active double-hit panels
    int nplanes =0; // number of planes hit
    int planespan =0; // span between first and last plane
    int nnullambig =0;  // number of hits without any ambiguity assigned
    int nmat =0, nmatactive =0; // number materials (straw) assigned and used (active) to this fit
    int nseg =0;     // number of trajectory segments
    float t0 =0;      // time this particle was estimated to cross z=0
    float t0err =-1;   // error on t0
    float chisq =-1;   // Kalman fit chisquared
    float fitcon =-1;  // Kalman fit chisqured consistency
    float radlen;  // total radiation length of (active) material crossed by this particle inside the tracker
    float firsthit =0, lasthit =0;  // first and last hit (time or distance)
    float maxgap =-1, avggap =-1; // fit trajectory gaps
    void reset() { *this = TrkInfo(); }
  };

  // general NC info about the particle which generated the majority of the hits used in this track
  struct TrkInfoMC {
    bool valid =false; // whether this information is valid or not
    int ndigi =0; // number of true straw digitizations (both ends) generatedy by the primary particle
    int  ndigigood =0; // number of true straw digitizations where the primary particle (not a delta-ray) crossed threshold
    int nhits =0, nactive =0; // number of hits on the track and active on the track generated by the primary particle
    int nambig =0; // number of true hits where the reconstruction assigned the correct left-right ambiguity
    int pdg =0, gen =0, proc =0; // true PDG code, generator code, and process code of the primary particle
    float otime =0;  // origin time
    MCRelationship prel =MCRelationship::none; // relationship if this tracks primary particle to the event primary
    XYZVectorF omom;  // origin momentum
    XYZVectorF opos;  // origin position
    void reset() { *this = TrkInfoMC(); }
  };
}
#endif
