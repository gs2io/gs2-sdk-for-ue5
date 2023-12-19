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


#include "Core/Domain/Model/TransactionConfiguration.h"

namespace Gs2::Core::Domain::Model
{
    FTransactionConfiguration::FTransactionConfiguration(
        const TOptional<FString> NamespaceName,
        const FStampTaskEvent StampTaskEventHandler,
        const FStampSheetEvent StampSheetEventHandler
    ):
        NamespaceName(NamespaceName.IsSet() ? NamespaceName : TOptional<FString>("default")),
        StampTaskEventHandler(StampTaskEventHandler),
        StampSheetEventHandler(StampSheetEventHandler)
    {
    }
    
    FTransactionConfiguration::FTransactionConfiguration(
        const FTransactionConfiguration& From
    ):
        NamespaceName(From.NamespaceName),
        StampTaskEventHandler(From.StampTaskEventHandler),
        StampSheetEventHandler(From.StampSheetEventHandler)
    {
    }
}