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

namespace Gs2::Buff::Request
{
    class FGetBuffEntryModelRequest;

    class GS2BUFF_API FGetBuffEntryModelRequest final : public TSharedFromThis<FGetBuffEntryModelRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BuffEntryNameValue;
        
    public:
        
        FGetBuffEntryModelRequest();
        FGetBuffEntryModelRequest(
            const FGetBuffEntryModelRequest& From
        );
        ~FGetBuffEntryModelRequest() = default;

        TSharedPtr<FGetBuffEntryModelRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBuffEntryModelRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBuffEntryModelRequest> WithBuffEntryName(const TOptional<FString> BuffEntryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBuffEntryName() const;

        static TSharedPtr<FGetBuffEntryModelRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBuffEntryModelRequest> FGetBuffEntryModelRequestPtr;
}