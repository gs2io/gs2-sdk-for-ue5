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
#include "../Model/AppleAppStoreContent.h"
#include "../Model/GooglePlayContent.h"

namespace Gs2::Money2::Request
{
    class FUpdateStoreContentModelMasterRequest;

    class GS2MONEY2_API FUpdateStoreContentModelMasterRequest final : public TSharedFromThis<FUpdateStoreContentModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ContentNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Model::FAppleAppStoreContent> AppleAppStoreValue;
        TSharedPtr<Model::FGooglePlayContent> GooglePlayValue;
        
    public:
        
        FUpdateStoreContentModelMasterRequest();
        FUpdateStoreContentModelMasterRequest(
            const FUpdateStoreContentModelMasterRequest& From
        );
        ~FUpdateStoreContentModelMasterRequest() = default;

        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithContentName(const TOptional<FString> ContentName);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithAppleAppStore(const TSharedPtr<Model::FAppleAppStoreContent> AppleAppStore);
        TSharedPtr<FUpdateStoreContentModelMasterRequest> WithGooglePlay(const TSharedPtr<Model::FGooglePlayContent> GooglePlay);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetContentName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<Model::FAppleAppStoreContent> GetAppleAppStore() const;
        TSharedPtr<Model::FGooglePlayContent> GetGooglePlay() const;

        static TSharedPtr<FUpdateStoreContentModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateStoreContentModelMasterRequest, ESPMode::ThreadSafe> FUpdateStoreContentModelMasterRequestPtr;
}