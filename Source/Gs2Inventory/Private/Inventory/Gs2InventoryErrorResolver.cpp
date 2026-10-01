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

#include "Inventory/Gs2InventoryErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Inventory/Error/ConflictError.h"
#include "Inventory/Error/InsufficientError.h"

namespace Gs2::Inventory
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Inventory"),
            &FGs2InventoryErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2InventoryErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("AcquireItemSetByUserId") || Method == TEXT("AcquireItemSetWithGradeByUserId") || Method == TEXT("AcquireSimpleItemsByUserId") || Method == TEXT("SetSimpleItemsByUserId") || Method == TEXT("AcquireBigItemByUserId") || Method == TEXT("SetBigItemByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("itemSet.operation.conflict")))
            {
                Resolved = MakeShared<Gs2::Inventory::Error::FConflictError>(Source);
            }
        }
        else if (Method == TEXT("ConsumeItemSet") || Method == TEXT("ConsumeItemSetByUserId") || Method == TEXT("ConsumeSimpleItems") || Method == TEXT("ConsumeSimpleItemsByUserId") || Method == TEXT("ConsumeBigItem") || Method == TEXT("ConsumeBigItemByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("itemSet.operation.conflict")))
            {
                Resolved = MakeShared<Gs2::Inventory::Error::FConflictError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("itemSet.count.insufficient")))
            {
                Resolved = MakeShared<Gs2::Inventory::Error::FInsufficientError>(Source);
            }
        }
        if (!Resolved.IsValid())
        {
            return Source;
        }
        Resolved->SetMetadata(Source->GetMetadata());
        return Resolved;
    }
}