/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (C) 2014 University of Arizona.
 *
 * Author: Jerald Paul Abraham <jeraldabraham@email.arizona.edu>
 */

#include <ndn-cpp-dev/face.hpp>
#include <ndn-cpp-dev/name.hpp>
#include <ndn-cpp-dev/interest.hpp>

namespace ndn {

  class NfdStatus
  {
  public:

    NfdStatus( char* toolName )
      : m_toolName(toolName)
      , m_versionRetrieval(false)
      , m_faceStatusRetrieval(false)
      , m_fibEnumerationRetrieval(false)
      , m_face()
    {
    }


    void
    usage()
    {
      std::cout << "\nUsage: " << m_toolName << " [options]\n"
        "Shows NFD Status Information\n"
        "Displays Version Information (NFD Version, Start Timestamp, Current Timestamp).\n"
        "Face Status Information via NFD Face Status Protocol (FaceID, URI, Counters).\n"
        "FIB Information via NFD FIB Enumeration Protocol (Prefix, Nexthop).\n"
        "If no options are provided, all information is retrieved.\n"
        "  [-v] - retrieve version information\n"
        "  [-f] - retrieve face status information\n"
        "  [-b] - retrieve FIB information\n"
        "  [-h] - print help and exit\n\n";
      exit(1);
    }

    void
    setVersionRetrieval()
    {
      m_versionRetrieval = true;
    }

    void
    setFaceStatusRetrieval()
    {
      m_faceStatusRetrieval = true;
    }

    void
    setFibEnumerationRetrieval()
    {
      m_fibEnumerationRetrieval = true;
    }

    void
    onData(
        const ndn::Interest& interest,
        ndn::Data& data,
        std::string informationType)
    {
      if (informationType == "Version")
        {
          //TBD
        }
      else if (informationType == "FaceStatus")
        {
          std::cout << "\nFace Status Protocol Data:\n";
          std::cout << data << std::endl;
        }
      else if (informationType == "FIB")
        {
          std::cout << "\nFIB Enumeration Protocol Data:\n";
          std::cout << data << std::endl;
        }
    }

    void
    onTimeout(
        const ndn::Interest& interest,
        std::string informationType)
    {
      if (informationType == "VersionDataRequest")
        {
          //TBD
        }
      else if (informationType == "FaceDataRequest")
        {
          std::cout << "\nTimeout For NFD Face Status Protocol" << std::endl;
        }
      else if (informationType == "FibDataRequest")
        {
          std::cout << "\nTimeout For NFD FIB Enumeration Protocol" << std::endl;
        }
    }

    void
    fetchVersionInformation()
    {
      //TBD: Waiting For Updated From Task #1199
    }

    void
    fetchFaceStatusInformation()
    {
      Name interestName("/localhost/nfd/faces/list");
      Interest interest(interestName);
      interest.setChildSelector(1);
      interest.setMustBeFresh(true);
      m_face.expressInterest(
        interest,
        func_lib::bind(&NfdStatus::onData, this, _1, _2, "FaceDataRequest"),
        func_lib::bind(&NfdStatus::onTimeout, this, _1, "FaceDataRequest"));
    }

    void
    fetchFibEnumerationInformation()
    {
      Name interestName("/localhost/nfd/fib/list");
      Interest interest(interestName);
      interest.setChildSelector(1);
      interest.setMustBeFresh(true);
      m_face.expressInterest(
        interest,
        func_lib::bind(&NfdStatus::onData, this, _1, _2, "FIBDataRequest"),
        func_lib::bind(&NfdStatus::onTimeout, this, _1, "FIBDataRequest"));
    }

    void
    fetchInformation()
    {
      if (!m_versionRetrieval && !m_faceStatusRetrieval && !m_fibEnumerationRetrieval)
        {
          setVersionRetrieval();
          setFaceStatusRetrieval();
          setFibEnumerationRetrieval();
        }
      if (m_versionRetrieval)
        {
          fetchVersionInformation();
        }
      if (m_faceStatusRetrieval)
        {
          fetchFaceStatusInformation();
        }
      if (m_fibEnumerationRetrieval)
        {
          fetchFibEnumerationInformation();
        }

      try {
        m_face.processEvents();
      }
      catch(std::exception &e) {
        std::cout << "ERROR: " << e.what() << std::endl;
      }
    }

  private:

    std::string m_toolName;
    bool m_versionRetrieval;
    bool m_faceStatusRetrieval;
    bool m_fibEnumerationRetrieval;
    Face m_face;

  };

}

int main( int argc, char* argv[] )
{
  int option;
  ndn::NfdStatus nfdStatus (argv[0]);

  while ((option = getopt(argc, argv, "hvfb")) != -1) {
    switch (option) {
    case 'h'  :
      nfdStatus.usage();
      break;
    case 'v'  :
      nfdStatus.setVersionRetrieval();
      break;
    case 'f'  :
      nfdStatus.setFaceStatusRetrieval();
      break;
    case 'b'  :
      nfdStatus.setFibEnumerationRetrieval();
      break;
    default   :
      nfdStatus.usage();
      break;
    }
  }

  nfdStatus.fetchInformation();

  return 0;
}





