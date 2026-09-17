/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Gs2Credential.h"

namespace Gs2::Core::Model
{
    class GS2CORE_API FProjectTokenGs2Credential final : public IGs2Credential, public TSharedFromThis<FProjectTokenGs2Credential>
    {
        FGs2ClientId ClientIdValue;
        FGs2ClientSecret ClientSecretValue;
        FGs2ProjectToken ProjectTokenValue;

    public:
        FProjectTokenGs2Credential(
            FString ClientId,
            FString ProjectToken
        );

        virtual const FGs2ClientId& ClientId() const override;
        virtual const FGs2ClientSecret& ClientSecret() const override;
        virtual const FGs2ProjectToken& ProjectToken() const override;
        virtual void UpdateProjectToken(const FGs2ProjectToken& Token) override;
        virtual bool IsProjectTokenCredential() const override { return true; }
    };
    typedef TSharedPtr<FProjectTokenGs2Credential, ESPMode::ThreadSafe> FProjectTokenGs2CredentialPtr;
}
