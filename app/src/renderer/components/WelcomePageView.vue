<template>
  <div>
    <div class="navbar-fixed">
      <nav>
        <div class="nav-wrapper">
          <a href="#" class="brand-logo">Prothesis</a>
       </div>
       <div class="nav-content">
        <ul class="tabs">
          <li class="tab"><a class="active" href="#test1">Details</a></li>
          <li class="tab"><a href="#test2">Assessments</a></li>
          <li class="tab"><a href="#test4">Themes Analysis</a></li>
          <li class="tab"><a href="#test4">Career guidance</a></li>
          <li class="tab"><a href="#test4">Mission statement</a></li>
        </ul>
      </div>
      </nav>
    </div>
    <div id="thePage" class="container">
      <div id="test1">
        <div class="row">

         <form class="col s12">
           <div class="row">
             <div class="input-field col s6">
               <input id="first_name" type="text" class="validate">
               <label for="first_name">First Name</label>
             </div>
             <div class="input-field col s6">
               <input id="last_name" type="text" class="validate">
               <label for="last_name">Last Name</label>
             </div>
           </div>
           <div class="row">
             <div class="input-field col s6">
               <input id="email" type="email" class="validate">
               <label for="email">Email</label>
             </div>
             <div class="input-field col s6">
               <input id="age" type="number" class="validate">
               <label for="number">Age</label>
             </div>
           </div>
         </form>
       </div>
     </div>
   </div>
  </div>
</template>

<script>
export default {
  data () {
    return {
      name: ''
    }
  },
  watch: {
    // Whenever question changes, this function will run.
    name: function () {
      // Matches atleast 2 words. (FirstName, LastName)
      var re = /^[a-z ,.'-]+(?:\s[a-z ,.'-]+)$/i
      if (this.name !== '' && re.test(this.name)) {
        document.getElementById('nextButton').disabled = false
      } else {
        document.getElementById('nextButton').disabled = true
      }
    }
  }
}
</script>

<style>
#thePage {
  margin-top: 60px;
}
</style>
