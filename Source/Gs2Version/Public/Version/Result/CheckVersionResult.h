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
#include "../Model/Status.h"

namespace Gs2::Version::Result
{
    class GS2VERSION_API FCheckVersionResult final : public TSharedFromThis<FCheckVersionResult>
    {
        TOptional<FString> ProjectTokenValue;
        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> WarningsValue;
        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> ErrorsValue;
        
    public:
        
        FCheckVersionResult();
        FCheckVersionResult(
            const FCheckVersionResult& From
        );
        ~FCheckVersionResult() = default;

        TSharedPtr<FCheckVersionResult> WithProjectToken(const TOptional<FString> ProjectToken);
        TSharedPtr<FCheckVersionResult> WithWarnings(const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Warnings);
        TSharedPtr<FCheckVersionResult> WithErrors(const TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> Errors);

        TOptional<FString> GetProjectToken() const;
        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> GetWarnings() const;
        TSharedPtr<TArray<TSharedPtr<Model::FStatus>>> GetErrors() const;

        static TSharedPtr<FCheckVersionResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCheckVersionResult, ESPMode::ThreadSafe> FCheckVersionResultPtr;
}