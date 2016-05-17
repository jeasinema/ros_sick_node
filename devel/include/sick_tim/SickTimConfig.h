//#line 2 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
// 
// File autogenerated for the sick_tim package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

#ifndef __sick_tim__SICKTIMCONFIG_H__
#define __sick_tim__SICKTIMCONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace sick_tim
{
  class SickTimConfigStatics;
  
  class SickTimConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(SickTimConfig &config, const SickTimConfig &max, const SickTimConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const SickTimConfig &config1, const SickTimConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, SickTimConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const SickTimConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, SickTimConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const SickTimConfig &config) const = 0;
      virtual void getValue(const SickTimConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T SickTimConfig::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (SickTimConfig::* field);

      virtual void clamp(SickTimConfig &config, const SickTimConfig &max, const SickTimConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const SickTimConfig &config1, const SickTimConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, SickTimConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const SickTimConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, SickTimConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const SickTimConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const SickTimConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, SickTimConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string name, std::string type, int parent, int id, bool s, T PT::* f) : AbstractGroupDescription(name, type, parent, id, s), field(f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, SickTimConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<SickTimConfig::AbstractGroupDescriptionConstPtr> groups;
    };
    
class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(SickTimConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("min_ang"==(*_i)->name){min_ang = boost::any_cast<double>(val);}
        if("max_ang"==(*_i)->name){max_ang = boost::any_cast<double>(val);}
        if("intensity"==(*_i)->name){intensity = boost::any_cast<bool>(val);}
        if("skip"==(*_i)->name){skip = boost::any_cast<int>(val);}
        if("frame_id"==(*_i)->name){frame_id = boost::any_cast<std::string>(val);}
        if("time_offset"==(*_i)->name){time_offset = boost::any_cast<double>(val);}
      }
    }

    double min_ang;
double max_ang;
bool intensity;
int skip;
std::string frame_id;
double time_offset;

    bool state;
    std::string name;

    
}groups;



//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double min_ang;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double max_ang;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool intensity;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int skip;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      std::string frame_id;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double time_offset;
//#line 218 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("SickTimConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }
    
    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const SickTimConfig &__max__ = __getMax__();
      const SickTimConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const SickTimConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const SickTimConfig &__getDefault__();
    static const SickTimConfig &__getMax__();
    static const SickTimConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();
    
  private:
    static const SickTimConfigStatics *__get_statics__();
  };
  
  template <> // Max and min are ignored for strings.
  inline void SickTimConfig::ParamDescription<std::string>::clamp(SickTimConfig &config, const SickTimConfig &max, const SickTimConfig &min) const
  {
    return;
  }

  class SickTimConfigStatics
  {
    friend class SickTimConfig;
    
    SickTimConfigStatics()
    {
SickTimConfig::GroupDescription<SickTimConfig::DEFAULT, SickTimConfig> Default("Default", "", 0, 0, true, &SickTimConfig::groups);
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.min_ang = -2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.min_ang = 2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.min_ang = -2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("min_ang", "double", 0, "The angle of the first range measurement [rad].", "", &SickTimConfig::min_ang)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("min_ang", "double", 0, "The angle of the first range measurement [rad].", "", &SickTimConfig::min_ang)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.max_ang = -2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.max_ang = 2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.max_ang = 2.35619449019;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("max_ang", "double", 0, "The angle of the last range measurement [rad].", "", &SickTimConfig::max_ang)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("max_ang", "double", 0, "The angle of the last range measurement [rad].", "", &SickTimConfig::max_ang)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.intensity = 0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.intensity = 1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.intensity = 1;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<bool>("intensity", "bool", 0, "Whether or not to return intensity values. RSSI output must be enabled on scanner (see wiki).", "", &SickTimConfig::intensity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<bool>("intensity", "bool", 0, "Whether or not to return intensity values. RSSI output must be enabled on scanner (see wiki).", "", &SickTimConfig::intensity)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.skip = 0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.skip = 9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.skip = 0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<int>("skip", "int", 0, "The number of scans to skip between each measured scan.", "", &SickTimConfig::skip)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<int>("skip", "int", 0, "The number of scans to skip between each measured scan.", "", &SickTimConfig::skip)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.frame_id = "";
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.frame_id = "";
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.frame_id = "laser";
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<std::string>("frame_id", "str", 0, "The TF frame in which laser scans will be returned.", "", &SickTimConfig::frame_id)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<std::string>("frame_id", "str", 0, "The TF frame in which laser scans will be returned.", "", &SickTimConfig::frame_id)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.time_offset = -0.25;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.time_offset = 0.25;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.time_offset = -0.001;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("time_offset", "double", 0, "An offset to add to the time stamp before publication of a scan [s].", "", &SickTimConfig::time_offset)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(SickTimConfig::AbstractParamDescriptionConstPtr(new SickTimConfig::ParamDescription<double>("time_offset", "double", 0, "An offset to add to the time stamp before publication of a scan [s].", "", &SickTimConfig::time_offset)));
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(SickTimConfig::AbstractGroupDescriptionConstPtr(new SickTimConfig::GroupDescription<SickTimConfig::DEFAULT, SickTimConfig>(Default)));
//#line 353 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<SickTimConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__); 
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__); 
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__); 
    }
    std::vector<SickTimConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<SickTimConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    SickTimConfig __max__;
    SickTimConfig __min__;
    SickTimConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const SickTimConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static SickTimConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &SickTimConfig::__getDescriptionMessage__() 
  {
    return __get_statics__()->__description_message__;
  }

  inline const SickTimConfig &SickTimConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }
  
  inline const SickTimConfig &SickTimConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }
  
  inline const SickTimConfig &SickTimConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }
  
  inline const std::vector<SickTimConfig::AbstractParamDescriptionConstPtr> &SickTimConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<SickTimConfig::AbstractGroupDescriptionConstPtr> &SickTimConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const SickTimConfigStatics *SickTimConfig::__get_statics__()
  {
    const static SickTimConfigStatics *statics;
  
    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = SickTimConfigStatics::get_instance();
    
    return statics;
  }


}

#endif // __SICKTIMRECONFIGURATOR_H__
