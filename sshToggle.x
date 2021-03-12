#import "sshToggle.h"

void setConfig(int);

@implementation test
- (UIImage *)iconGlyph
{
    return [UIImage imageNamed:@"Icon" inBundle:[NSBundle bundleForClass:[self class]] compatibleWithTraitCollection:nil];
}

- (UIColor *)selectedColor
{
	return [UIColor blueColor];
}

- (BOOL)isSelected
{
    return _selected;
}

- (void)setSelected:(BOOL)selected
{
    _selected = selected;
    [super refreshState];
    setConfig(_selected);
}
@end
