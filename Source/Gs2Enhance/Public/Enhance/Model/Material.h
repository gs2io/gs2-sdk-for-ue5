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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FMaterial final : public FGs2Object, public TSharedFromThis<FMaterial>
    {
        TOptional<FString> MaterialItemSetIdValue;
        TOptional<int32> CountValue;

    public:
        FMaterial();
        FMaterial(
            const FMaterial& From
        );
        virtual ~FMaterial() override = default;

        TSharedPtr<FMaterial> WithMaterialItemSetId(const TOptional<FString> MaterialItemSetId);
        TSharedPtr<FMaterial> WithCount(const TOptional<int32> Count);

        TOptional<FString> GetMaterialItemSetId() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FMaterial> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMaterial, ESPMode::ThreadSafe> FMaterialPtr;
}