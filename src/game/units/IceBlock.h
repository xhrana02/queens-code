//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Unit.h"
#include "Field.h"

class IceBlock : public Unit
{
    fsg::RenderingObject* iceBlockObject = nullptr;

public:
    IceBlock();

    // custom overrides
    PlayerID GetOwnerID() const override;
    fsg::RenderingObject* GetRenderingObject() const override;
    void SetIceBlockObject(fsg::RenderingObject* newRenderingObject);
    int TakeDamage(AttackType attackType, int damageNormal, int damageHP = 0, int damageEN = 0) override;

    // return 0 overrides
    int Heal(int healHP, int healEN = 0) override { return 0; }
    int TakeTheoreticalDamage(AttackType attackType, int damageNormal, int damageHP = 0, int damageEN = 0) override { return 0; }
    int TheoreticalHeal(int healHP, int healEN = 0) override { return 0; }

    // do nothing overrides
    void ApplyBuff(Buff* newBuff) override {}
    void OnUnitDeath() override {}
};
