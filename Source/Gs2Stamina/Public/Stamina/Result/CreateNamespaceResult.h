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
#include "../Model/Namespace.h"

namespace Gs2::Stamina::Result
{
    class GS2STAMINA_API FCreateNamespaceResult final : public TSharedFromThis<FCreateNamespaceResult>
    {
        TSharedPtr<Model::FNamespace> ItemValue;
        
    public:
        
        FCreateNamespaceResult();
        FCreateNamespaceResult(
            const FCreateNamespaceResult& From
        );
        ~FCreateNamespaceResult() = default;

        TSharedPtr<FCreateNamespaceResult> WithItem(const TSharedPtr<Model::FNamespace> Item);

        TSharedPtr<Model::FNamespace> GetItem() const;

        static TSharedPtr<FCreateNamespaceResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNamespaceResult, ESPMode::ThreadSafe> FCreateNamespaceResultPtr;
}