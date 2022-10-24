#include "CategorySelector.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#ifdef MARLIN_USE_AIDA
#include <marlin/AIDAProcessor.h>
#include <AIDA/IHistogramFactory.h>
#include <AIDA/ICloud1D.h>
//#include <AIDA/IHistogram1D.h>
#endif // MARLIN_USE_AIDA


using namespace lcio ;
using namespace marlin ;


CategorySelector aCategorySelector ;


CategorySelector::CategorySelector() : Processor("CategorySelector") {

    // modify processor description
    _description = "CategorySelector does whatever it does ..." ;


    registerProcessorParameter( "DesiredCategory",
                                "Choose A, B, C or D ",
                                DesiredCategory,
                                std::string("A"));

    // register steering parameters: name, description, class-variable, default value
    registerInputCollection( LCIO::MCPARTICLE,
            "CollectionName" , 
            "Name of the MCParticle collection"  ,
            _colName ,
            std::string("MCParticle")
    );
}



void CategorySelector::init() { 

    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    // usually a good idea to
    printParameters() ;

    _nRun = 0 ;
    _nEvt = 0 ;

}


void CategorySelector::processRunHeader( LCRunHeader* run) { 

    _nRun++ ;
} 



void CategorySelector::processEvent( LCEvent * evt ) { 


  if (!_jets) {
    Event::Instance()->Get(_jetname.c_str(), _jets);
  }
  //const Vertex * privtx = Event::Instance()->getPrimaryVertex();                                                                                                                             

  vector<double> btags, ctags;

  for (unsigned int nj = 0; nj < _jets->size(); nj++) {
    const Jet* j = (*_jets)[nj];

    const Parameters* para = j->getParam("lcfiplus");
    _nt->Fill(_nev, nj, j->E(), j->Px(), j->Py(), j->Pz(),
              para->get<double>("BTag"), para->get<double>("CTag"), para->get<double>("OTag"),  para->get<double>("BBTag"),  para->get<double>("CCTag"),  para->get<double>("BCTag"));
    btags.push_back(para->get<double>("BTag"));
    ctags.push_back(para->get<double>("CTag"));

    cout << "nvtx = " << para->get<double>("nvtx") << ", nvtxall = " << para->get<double>("nvtxall") << endl;
  }

    // this gets called for every event 
    // usually the working horse ...


#ifdef MARLIN_USE_AIDA

    // define a histogram pointer
    static AIDA::ICloud1D* hMCPEnergy ;    

    if( isFirstEvent() ) { 

        hMCPEnergy = AIDAProcessor::histogramFactory(this)->
            createCloud1D( "hMCPEnergy", "energy of the MCParticles", 100 ) ; 

    }
#endif // MARLIN_USE_AIDA

    // try to get lcio collection (exits if collection is not available)
    // NOTE: if the AIDAProcessor is activated in your steering file and Marlin is linked with
    //      RAIDA you may get the message: "*** Break *** segmentation violation" followed by a
    //      stack-trace (generated by ROOT) in case the collection is unavailable. This happens
    //      because ROOT is somehow catching the exit signal commonly used to exit a program
    //      intentionally. Sorry if this messsage may confuse you. Please ignore it!
    LCCollection* col = evt->getCollection( _colName ) ;


    // Alternativelly if you do not want Marlin to exit in case of a non-existing collection
    // use the following (commented out) code:
    //LCCollection* col = NULL;
    //try{
    //    col = evt->getCollection( _colName );
    //}
    //catch( lcio::DataNotAvailableException e )
    //{
    //    streamlog_out(WARNING) << _colName << " collection not available" << std::endl;
    //    col = NULL;
    //}

    // this will only be entered if the collection is available
    if( col != NULL ){

        int nMCP = col->getNumberOfElements()  ;

        for(int i=0; i< nMCP ; i++){

            MCParticle* p = dynamic_cast<MCParticle*>( col->getElementAt( i ) ) ;

#ifdef MARLIN_USE_AIDA
            // fill histogram from LCIO data :
            hMCPEnergy->fill( p->getEnergy() ) ;
#endif
        } 
    }



    //-- note: this will not be printed if compiled w/o MARLINDEBUG=1 !

    streamlog_out(DEBUG) << "   processing event: " << evt->getEventNumber() 
        << "   in run:  " << evt->getRunNumber() << std::endl ;



    _nEvt ++ ;
}



void CategorySelector::check( LCEvent * evt ) { 
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void CategorySelector::end(){ 

    //   std::cout << "CategorySelector::end()  " << name() 
    // 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
    // 	    << std::endl ;

}

