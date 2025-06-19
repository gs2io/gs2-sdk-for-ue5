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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Core::Model
{
    class GS2ACCOUNT_API FResultMetadata final : public FGs2Object, public TSharedFromThis<FResultMetadata>
    {
        FString UncommittedValue;

    public:
        FResultMetadata();
        FResultMetadata(
            const FResultMetadata& From
        );
        virtual ~FResultMetadata() override = default;

        TSharedPtr<FResultMetadata> WithUncommitted(const FString Uncommitted);

        FString GetUncommitted() const;


        static TSharedPtr<FResultMetadata> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FResultMetadata, ESPMode::ThreadSafe> FResultMetadataPtr;
}