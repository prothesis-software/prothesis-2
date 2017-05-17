<template>
  <div class="container-fluid">
    <div class="row">
      <div class="col-md-4">
        <h1>Welcome {{ name }}!</h1>
      </div>
    </div>
    <div class = "row">
      <div class="col-md-4">
        <form>
          <input id="enterName" v-model="name" class="form-control" placeholder="Enter your full name">
          <button id="nextButton" class="btn btn-primary" style="margin-top: 15px" disabled="true">Next</button>
        </form>
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
      // Mathes atleast 2 words. (FirstName, LastName)
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
</style>
