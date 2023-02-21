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
#include "Identifier/Gs2Identifier.h"

namespace Gs2::Identifier::Domain::Iterator
{

    class FDescribeSecurityPoliciesIteratorLoadTask;

    class GS2IDENTIFIER_API FDescribeSecurityPoliciesIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Identifier::Model::FSecurityPolicy, FDescribeSecurityPoliciesIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        friend FDescribeSecurityPoliciesIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeSecurityPoliciesIteratorLoadTask>> Load() override;

public:
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeSecurityPoliciesIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Identifier::FGs2IdentifierRestClientPtr Client
        );

        class GS2IDENTIFIER_API IteratorImpl
        {
            friend FDescribeSecurityPoliciesIterator;

            TSharedPtr<FAsyncTask<Gs2::Identifier::Domain::Iterator::FDescribeSecurityPoliciesIterator::FNextTask>> Task;
            Gs2::Identifier::Model::FSecurityPolicyPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Identifier::Domain::Iterator::FDescribeSecurityPoliciesIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Identifier::Model::FSecurityPolicyPtr& operator*() const;
            Gs2::Identifier::Model::FSecurityPolicyPtr operator->();
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
    typedef TSharedPtr<FDescribeSecurityPoliciesIterator> FDescribeSecurityPoliciesIteratorPtr;

    class FDescribeSecurityPoliciesIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Identifier::Model::FSecurityPolicyPtr>>,
        public TSharedFromThis<FDescribeSecurityPoliciesIteratorLoadTask>
    {
        TSharedPtr<FDescribeSecurityPoliciesIterator> Self;

    public:
        explicit FDescribeSecurityPoliciesIteratorLoadTask(
            TSharedPtr<FDescribeSecurityPoliciesIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Identifier::Model::FSecurityPolicyPtr>>> Result
        ) override;
    };
}
