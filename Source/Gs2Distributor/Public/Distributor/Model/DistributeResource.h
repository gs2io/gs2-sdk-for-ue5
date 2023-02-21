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

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FDistributeResource final : public TSharedFromThis<FDistributeResource>
    {
        TOptional<FString> ActionValue;
        TOptional<FString> RequestValue;

    public:
        FDistributeResource();
        FDistributeResource(
            const FDistributeResource& From
        );
        ~FDistributeResource() = default;

        TSharedPtr<FDistributeResource> WithAction(const TOptional<FString> Action);
        TSharedPtr<FDistributeResource> WithRequest(const TOptional<FString> Request);

        TOptional<FString> GetAction() const;
        TOptional<FString> GetRequest() const;


        static TSharedPtr<FDistributeResource> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDistributeResource, ESPMode::ThreadSafe> FDistributeResourcePtr;
}