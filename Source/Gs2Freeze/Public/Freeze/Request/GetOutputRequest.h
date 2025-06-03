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
#include "Dom/JsonObject.h"

namespace Gs2::Freeze::Request
{
    class FGetOutputRequest;

    class GS2FREEZE_API FGetOutputRequest final : public TSharedFromThis<FGetOutputRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> StageNameValue;
        TOptional<FString> OutputNameValue;
        
    public:
        
        FGetOutputRequest();
        FGetOutputRequest(
            const FGetOutputRequest& From
        );
        ~FGetOutputRequest() = default;

        TSharedPtr<FGetOutputRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetOutputRequest> WithStageName(const TOptional<FString> StageName);
        TSharedPtr<FGetOutputRequest> WithOutputName(const TOptional<FString> OutputName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetStageName() const;
        TOptional<FString> GetOutputName() const;

        static TSharedPtr<FGetOutputRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetOutputRequest> FGetOutputRequestPtr;
}