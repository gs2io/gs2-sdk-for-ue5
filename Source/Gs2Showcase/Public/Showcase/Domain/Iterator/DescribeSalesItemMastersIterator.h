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
#include "Showcase/Gs2Showcase.h"

namespace Gs2::Showcase::Domain::Iterator
{

    class FDescribeSalesItemMastersIteratorLoadTask;

    class GS2SHOWCASE_API FDescribeSalesItemMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Showcase::Model::FSalesItemMaster, FDescribeSalesItemMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client;

        friend FDescribeSalesItemMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeSalesItemMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeSalesItemMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2SHOWCASE_API IteratorImpl
        {
            friend FDescribeSalesItemMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Showcase::Domain::Iterator::FDescribeSalesItemMastersIterator::FNextTask>> Task;
            Gs2::Showcase::Model::FSalesItemMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Showcase::Domain::Iterator::FDescribeSalesItemMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Showcase::Model::FSalesItemMasterPtr& operator*() const;
            Gs2::Showcase::Model::FSalesItemMasterPtr operator->();
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
    typedef TSharedPtr<FDescribeSalesItemMastersIterator> FDescribeSalesItemMastersIteratorPtr;

    class FDescribeSalesItemMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>>,
        public TSharedFromThis<FDescribeSalesItemMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribeSalesItemMastersIterator> Self;

    public:
        explicit FDescribeSalesItemMastersIteratorLoadTask(
            TSharedPtr<FDescribeSalesItemMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Showcase::Model::FSalesItemMasterPtr>>> Result
        ) override;
    };
}
