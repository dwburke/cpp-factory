
#pragma once

// optionally create additional Args that are passed to the constructor
// class ObjTypeFactory : public Factory<obj_type_generic, int, obj_data *> {
// class ObjTypeFactory : public Factory<parent_class, std::string> {

template <typename T, typename KEYT, typename... Args>
class Factory {
   public:
   template <typename TDerived>
   void registerType(KEYT key)
   {
      static_assert(std::is_base_of<T, TDerived>::value, "Factory::registerType doesn't accept this type because doesn't derive from base class");
      _createFuncs[key] = &createFunc<TDerived>;
   }

   std::shared_ptr<T> create(KEYT key, Args... args)
   {
      try {
         auto f = _createFuncs.at(key);
         return f(args...);
      } catch (const std::out_of_range &) {
         throw std::range_error(
             fmt::format("key [{}] is not registered", key));
      }
   }

   bool contains(KEYT key)
   {
      return _createFuncs.contains(key);
   }

   private:
   template <typename TDerived>
   static std::shared_ptr<T> createFunc(Args... args)
   {
      return std::shared_ptr<TDerived>(new TDerived(args...));
   }

   typedef std::shared_ptr<T> (*PCreateFunc)(Args...);
   std::map<KEYT, PCreateFunc> _createFuncs;
};

