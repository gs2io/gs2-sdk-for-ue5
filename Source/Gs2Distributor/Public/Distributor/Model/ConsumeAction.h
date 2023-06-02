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

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FConsumeAction final : public Gs2Object, public TSharedFromThis<FConsumeAction>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

    public:
        FConsumeAction();
        FConsumeAction(
            const FConsumeAction& From
        );
        virtual ~FConsumeAction() override = default;

        TSharedPtr<FConsumeAction> WithAction(const TOptional<FString> Action);
        TSharedPtr<FConsumeAction> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetRequest() const;


        static TSharedPtr<FConsumeAction> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FConsumeAction, ESPMode::ThreadSafe> FConsumeActionPtr;
}