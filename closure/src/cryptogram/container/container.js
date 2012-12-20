goog.provide('cryptogram.container');

goog.require('goog.dom');

/**
 * @constructor
 */
cryptogram.container = function(img, node) {

  this.img = img;
  this.createStatus();
  
  if (node == null) {
    node = img.parentNode;
  }
  if (node) {
    node.insertBefore(this.div, node.childNodes[0]);
  }

};


cryptogram.container.prototype.createStatus = function() {
  this.div = goog.dom.createDom('div', { 'class': 'status'});
  this.div.style.display = 'none';
  this.div.style.position = "absolute";
  this.div.style.width = "50px";
  this.div.style.top = "0px";
  this.div.style.margin = "5px";
  this.div.style.marginLeft = "5px";
  this.div.style.padding = "5px";
  this.div.style.color = "black";
  this.div.style.background = "white";
  this.div.style.opacity = "0.8";
  this.div.style.font = "10px arial";
  this.div.style.textAlign = "center";
  this.div.style.borderRadius = "3px";
  this.div.style.left = this.img.width / 2;
};

cryptogram.container.prototype.remove = function() {
  this.div.parentNode.removeChild(this.div);  
};


cryptogram.container.prototype.getSrc = function() {
  return this.img.src;
};


cryptogram.container.prototype.setSrc = function(src) {    
  this.previousSrc = this.img.src;
  this.img.src = src;
};


cryptogram.container.prototype.revertSrc = function() {
    if (!this.previousSrc) return;    
    this.img.src = this.previousSrc; 
    this.previousSrc = null;
};

cryptogram.container.prototype.setStatus = function(status) {
  if (!status) {
    this.div.innerHTML = '';
    this.div.style.display = 'none';
  } else {
    this.div.innerHTML = status;  
    this.div.style.display = '';
  }
};