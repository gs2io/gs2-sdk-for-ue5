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

namespace Gs2::Mission::Request
{
    class FDescribeMissionGroupModelMastersRequest;

    class GS2MISSION_API FDescribeMissionGroupModelMastersRequest final : public TSharedFromThis<FDescribeMissionGroupModelMastersRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeMissionGroupModelMastersRequest();
        FDescribeMissionGroupModelMastersRequest(
            const FDescribeMissionGroupModelMastersRequest& From
        );
        ~FDescribeMissionGroupModelMastersRequest() = default;

        TSharedPtr<FDescribeMissionGroupModelMastersRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeMissionGroupModelMastersRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeMissionGroupModelMastersRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeMissionGroupModelMastersRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeMissionGroupModelMastersRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeMissionGroupModelMastersRequest, ESPMode::ThreadSafe> FDescribeMissionGroupModelMastersRequestPtr;
}