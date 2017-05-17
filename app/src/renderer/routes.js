export default [
  {
    path: '/',
    name: 'welcome-page',
    component: require('components/WelcomePageView')
  },
  {
    path: '*',
    redirect: '/'
  }
]
