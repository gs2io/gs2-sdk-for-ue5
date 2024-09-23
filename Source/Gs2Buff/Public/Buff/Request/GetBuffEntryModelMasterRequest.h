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

namespace Gs2::Buff::Request
{
    class FGetBuffEntryModelMasterRequest;

    class GS2BUFF_API FGetBuffEntryModelMasterRequest final : public TSharedFromThis<FGetBuffEntryModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> BuffEntryNameValue;
        
    public:
        
        FGetBuffEntryModelMasterRequest();
        FGetBuffEntryModelMasterRequest(
            const FGetBuffEntryModelMasterRequest& From
        );
        ~FGetBuffEntryModelMasterRequest() = default;

        TSharedPtr<FGetBuffEntryModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetBuffEntryModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetBuffEntryModelMasterRequest> WithBuffEntryName(const TOptional<FString> BuffEntryName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetBuffEntryName() const;

        static TSharedPtr<FGetBuffEntryModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetBuffEntryModelMasterRequest, ESPMode::ThreadSafe> FGetBuffEntryModelMasterRequestPtr;
}