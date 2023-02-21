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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Inventory/Gs2Inventory.h"

namespace Gs2::Inventory::Domain::Iterator
{

    class FDescribeItemModelsIteratorLoadTask;

    class GS2INVENTORY_API FDescribeItemModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Inventory::Model::FItemModel, FDescribeItemModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client;

        friend FDescribeItemModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeItemModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> InventoryName;
        TOptional<int32> FetchSize;

        FDescribeItemModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> InventoryName
        );

        class GS2INVENTORY_API IteratorImpl
        {
            friend FDescribeItemModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FNextTask>> Task;
            Gs2::Inventory::Model::FItemModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Inventory::Model::FItemModelPtr& operator*() const;
            Gs2::Inventory::Model::FItemModelPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeItemModelsIterator> FDescribeItemModelsIteratorPtr;

    class FDescribeItemModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Inventory::Model::FItemModelPtr>>,
        public TSharedFromThis<FDescribeItemModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeItemModelsIterator> Self;

    public:
        explicit FDescribeItemModelsIteratorLoadTask(
            TSharedPtr<FDescribeItemModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemModelPtr>>> Result
        ) override;
    };
}
