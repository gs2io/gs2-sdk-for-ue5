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
#include "Money2/Model/StoreContentModel.h"
#include "Gs2Money2EzAppleAppStoreContent.h"
#include "Gs2Money2EzGooglePlayContent.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzStoreContentModel final : public TSharedFromThis<FEzStoreContentModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Gs2::UE5::Money2::Model::FEzAppleAppStoreContent> AppleAppStoreValue;
        TSharedPtr<Gs2::UE5::Money2::Model::FEzGooglePlayContent> GooglePlayValue;

	public:
        TSharedPtr<FEzStoreContentModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzStoreContentModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzStoreContentModel> WithAppleAppStore(const TSharedPtr<Gs2::UE5::Money2::Model::FEzAppleAppStoreContent> AppleAppStore);
        TSharedPtr<FEzStoreContentModel> WithGooglePlay(const TSharedPtr<Gs2::UE5::Money2::Model::FEzGooglePlayContent> GooglePlay);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<Gs2::UE5::Money2::Model::FEzAppleAppStoreContent> GetAppleAppStore() const;

        TSharedPtr<Gs2::UE5::Money2::Model::FEzGooglePlayContent> GetGooglePlay() const;

        Gs2::Money2::Model::FStoreContentModelPtr ToModel() const;
        static TSharedPtr<FEzStoreContentModel> FromModel(Gs2::Money2::Model::FStoreContentModelPtr Model);
    };
    typedef TSharedPtr<FEzStoreContentModel> FEzStoreContentModelPtr;
}