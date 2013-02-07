


// =-=-=-=-=-=-=-
// e-irods includes
#include "eirods_plugin_base.h"

namespace eirods {

    // =-=-=-=-=-=-=-
    // public - constructor 
    plugin_base::plugin_base( const std::string& _n,
                              const std::string& _c ) : 
                              context_( _c ),
                              instance_name_( _n ) {
    } // ctor

    // =-=-=-=-=-=-=-
    // public - copy constructor 
    plugin_base::plugin_base( const plugin_base& _rhs ) :
                              context_( context_ ),
                              instance_name_( _rhs.instance_name_ ) {
    } // cctor

    // =-=-=-=-=-=-=-
    // public - assignment operator
    plugin_base& plugin_base::operator=( const plugin_base& _rhs ) {
        instance_name_ = _rhs.instance_name_;
        context_       = context_;

        return *this;

    } // operator=

    // =-=-=-=-=-=-=-
    // public - destructor 
    plugin_base::~plugin_base(  ) {
    } // dtor

    // =-=-=-=-=-=-=-
    // public - default implementation
    //error plugin_base::post_disconnect_maintenance_operation( pdmo_base*& _op ) {
    error plugin_base::post_disconnect_maintenance_operation( pdmo_type& _op ) {
       return ERROR( -1, "no defined operation" );
        
    } // post_disconnect_maintenance_operation
 
    // =-=-=-=-=-=-=-
    // public - interface to determine if a PDMO is necessary
    error plugin_base::need_post_disconnect_maintenance_operation( bool& _b ) {
        _b = false;
        return SUCCESS();
    } // need_post_disconnect_maintenance_operation


    // =-=-=-=-=-=-=-
    // public - add an operation to the map given a key.  provide the function name such that it
    //          may be loaded from the shared object later via delay_load
    error plugin_base::add_operation( std::string _op, 
                                      std::string _fcn_name ) {
        // =-=-=-=-=-=-=-
        // check params 
        if( _op.empty() ) {
            std::stringstream msg;
            msg << "add_operation - empty operation [" << _op << "]";
            return ERROR( -1, msg.str() );
        }
                
        if( _fcn_name.empty() ) {
            std::stringstream msg;
            msg << "add_operation - empty function name [" 
                << _fcn_name << "]";
            return ERROR( -1, msg.str() );
        }

        // =-=-=-=-=-=-=-
        // add operation string to the vector
        ops_for_delay_load_.push_back( std::pair< std::string, std::string >( _op, _fcn_name ) );
                
        return SUCCESS();

    } //  add_operation

    // =-=-=-=-=-=-=-
    // public - get a list of all the available operations
    error plugin_base::enumerate_operations( std::vector< std::string >& _ops ) {
       for( size_t i = 0; i < ops_for_delay_load_.size(); ++i ) {
           _ops.push_back( ops_for_delay_load_[ i ].first );
       }

       return SUCCESS();

    } // enumerate_operations

}; // namespace eirods



