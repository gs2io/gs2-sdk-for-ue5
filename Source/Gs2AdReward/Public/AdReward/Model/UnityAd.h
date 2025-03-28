/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::AdReward::Model
{
    class GS2ADREWARD_API FUnityAd final : public FGs2Object, public TSharedFromThis<FUnityAd>
    {
        TSharedPtr<TArray<FString>> KeysValue;

    public:
        FUnityAd();
        FUnityAd(
            const FUnityAd& From
        );
        virtual ~FUnityAd() override = default;

        TSharedPtr<FUnityAd> WithKeys(const TSharedPtr<TArray<FString>> Keys);

        TSharedPtr<TArray<FString>> GetKeys() const;


        static TSharedPtr<FUnityAd> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FUnityAd, ESPMode::ThreadSafe> FUnityAdPtr;
}